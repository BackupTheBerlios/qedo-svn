/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/


#include "Unzip.h"


void Unzip::change_file_date(const char* filename,uLong dosdate,tm_unz tmu_date) {
#ifdef _WINDOWS
  HANDLE hFile;
  FILETIME ftm,ftLocal,ftCreate,ftLastAcc,ftLastWrite;

  hFile = CreateFile(filename,GENERIC_READ | GENERIC_WRITE,
        		0,NULL,OPEN_EXISTING,0,NULL);
  GetFileTime(hFile,&ftCreate,&ftLastAcc,&ftLastWrite);
  DosDateTimeToFileTime((WORD)(dosdate>>16),(WORD)dosdate,&ftLocal);
  LocalFileTimeToFileTime(&ftLocal,&ftm);
  SetFileTime(hFile,&ftm,&ftLastAcc,&ftm);
  CloseHandle(hFile);
#else
#ifdef unix
  struct utimbuf ut;
  struct tm newdate;
  newdate.tm_sec = tmu_date.tm_sec;
  newdate.tm_min=tmu_date.tm_min;
  newdate.tm_hour=tmu_date.tm_hour;
  newdate.tm_mday=tmu_date.tm_mday;
  newdate.tm_mon=tmu_date.tm_mon;
  if (tmu_date.tm_year > 1900)
    newdate.tm_year=tmu_date.tm_year - 1900;
  else
    newdate.tm_year=tmu_date.tm_year ;
  newdate.tm_isdst=-1;

  ut.actime=ut.modtime=mktime(&newdate);
  utime(filename,&ut);
#endif
#endif
}

int Unzip::mymkdir(const char* dirname) {
  int ret=0;
#ifdef _WINDOWS
  ret = mkdir(dirname);
#else
#ifdef unix
  ret = mkdir (dirname,0775);
#endif
#endif
  return(ret);
}

int Unzip::makedir(char* newdir) {
  char *buffer ;
  char *p;
  int  len = strlen(newdir);

  if (len <= 0)
    return(0);

  buffer = (char*)malloc(len+1);
  strcpy(buffer,newdir);

  if (buffer[len-1] == '/') {
    buffer[len-1] = '\0';
  }
  if (mymkdir(buffer) == 0) {
    free(buffer);
    return(1);
  }
  p = buffer+1;
  while (1) {
    char hold;

    while(*p && *p != '\\' && *p != '/')
      p++;
    hold = *p;
    *p = 0;
    if ((mymkdir(buffer) == -1) && (errno == ENOENT)) {
//      std::cout << "Couldn't create directory " << buffer<< endl;
      free(buffer);
      return(0);
    }
    if (hold == 0)
      break;
    *p++ = hold;
  }
  free(buffer);
  return 1;
}

int Unzip::do_extract_currentfile(unzFile uf,const int* popt_extract_without_path,int* popt_overwrite) {
  char filename_inzip[256];
  char* filename_withoutpath;
  char* p;
  int err=UNZ_OK;
  FILE *fout=NULL;
  void* buf;
  uInt size_buf;
  unz_file_info file_info;
  uLong ratio=0;

  err = unzGetCurrentFileInfo(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
  if (err!=UNZ_OK) {
//    std::cout<< "Error " << err << " with zipfile in unzGetCurrentFileInfo\n";
    return(err);
  }

  size_buf = WRITEBUFFERSIZE;
  buf = (void*)malloc(size_buf);
  if (buf==NULL) {
//    std::cout << "Error allocating memory\n";
    return UNZ_INTERNALERROR;
  }

  p = filename_withoutpath = filename_inzip;
  while ((*p) != '\0') {
    if (((*p)=='/') || ((*p)=='\\'))
      filename_withoutpath = p+1;
      p++;
   }

  if ((*filename_withoutpath)=='\0') {
    if ((*popt_extract_without_path)==0) {
//      std::cout << "Creating directory: " << filename_inzip << endl;
      mymkdir(filename_inzip);
    }
  }
  else {
//    const char* write_filename;
    char* write_filename;
    int skip=0;

    if ((*popt_extract_without_path)==0)
      write_filename = filename_inzip;
    else
      write_filename = filename_withoutpath;

    err = unzOpenCurrentFile(uf);
    if (err!=UNZ_OK)
//      std::cout << "Error " << err << " with zipfile in unzOpenCurrentFile\n";

    if (((*popt_overwrite)==0) && (err==UNZ_OK)) {
      FILE* ftestexist;
      ftestexist = fopen(write_filename,"rb");
      if (ftestexist!=NULL)
        fclose(ftestexist);

      *popt_overwrite=1;
    }

    if ((skip==0) && (err==UNZ_OK)) {
      fout=fopen(write_filename,"wb");

/* some zipfile don't contain directory alone before file */
      if ((fout==NULL) && ((*popt_extract_without_path)==0) && (filename_withoutpath!=(char*)filename_inzip)) {
        char c=*(filename_withoutpath-1);
        *(filename_withoutpath-1)='\0';
        makedir(write_filename);
        *(filename_withoutpath-1)=c;
        fout=fopen(write_filename,"wb");
      }

//      if (fout==NULL)
//        std::cout << "Error opening " << write_filename<< endl;
    }

    if (fout!=NULL) {
//      std::cout << "Extracting: " << write_filename<< endl;

      do {
        err = unzReadCurrentFile(uf,buf,size_buf);
        if (err<0) {
//          std::cout << "Error " << err << " with zipfile in unzReadCurrentFile\n";
          break;
        }
        if (err>0)
          if (fwrite(buf,err,1,fout)!=1) {
//            std::cout << "Error in writing extracted file\n";
            err=UNZ_ERRNO;
            break;
          }
      }
      while (err>0);
      fclose(fout);
      if (err==0)
        change_file_date(write_filename,file_info.dosDate,file_info.tmu_date);
    }

    if (err==UNZ_OK) {
      err = unzCloseCurrentFile (uf);
//      if (err!=UNZ_OK)
//        std::cout << "Error " << err << " with zipfile in unzCloseCurrentFile\n";
    } else
      unzCloseCurrentFile(uf); /* don't lose the error */
  }
  free(buf);
  return(err);
}

int Unzip::do_extract_onefile(unzFile uf,std::string filename,int opt_extract_without_path,int opt_overwrite) {
  int err = UNZ_OK;
  if (unzLocateFile(uf,filename.c_str(),CASESENSITIVITY)!=UNZ_OK) {
//	  std::cout << "File " << filename.c_str() << " not found in the zipfile\n";
    return 2;
  }
  if (do_extract_currentfile(uf,&opt_extract_without_path,&opt_overwrite) == UNZ_OK)
    return 0;
  else
    return 1;
}


// Constructor of the Unzip class.
// The file parameter is the absolute or relative
// pathname of the archive file.

Unzip::Unzip(std::string file) 
{
  _zipfilename = file;
}


// This function returns the pathname of the
// descriptor file within the archive.
// If the format of the archive is not correct or
// if there is no .csd file or if there are more
// than one .csd file, the string "" is returned.

void Unzip::find_files_with_end(FoundFileList& descriptors, std::string file_end) 
{
  //std::string csdfile("");
  unzFile uf = unzOpen(_zipfilename.c_str());
  if (uf == NULL) 
  { // the format of the archive is not correct or the archive file does not exist
	  std::cerr << "Cannot open " << _zipfilename.c_str() << " to find the descriptor file\n";
	throw ArchiveOpenError_err ("the format of the archive is not correct or the archive file does not exist !!!\n")  ; // the string "" is returned
  }

  uLong i;
  unz_global_info gi;
  int err;

  err = unzGetGlobalInfo (uf,&gi);
//  if (err!=UNZ_OK)
//    std::cout << "Error " << err << " with zipfile in unzGetGlobalInfo \n";

  for (i=0 ; i<gi.number_entry ; i++) 
  {
    char filename_inzip[256];
    unz_file_info file_info;

    err = unzGetCurrentFileInfo(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
    if (err!=UNZ_OK) 
	{
     std::cerr << "Error " << err << " with zipfile in unzGetCurrentFileInfo\n";
     throw ArchiveInfo_err ("Error in unzGetCurrentFileInfo !!!\n ");
    }

    std::string filename(filename_inzip);
    int j = filename.find(file_end);
    if ((j >= 0) && (j < filename.size()))
	{ 
		descriptors.push_back( filename );
		if ((i+1)<gi.number_entry) 
		{
			err = unzGoToNextFile(uf);
			if (err!=UNZ_OK) 
			{
				std::cerr << "Error " << err << " with zipfile in unzGoToNextFile\n";
				throw GoToNextFile_err ("Error in unzGoToNextFile !!!\n ");
			}
		}
	}
	else
    if ((i+1)<gi.number_entry) 
	{
      err = unzGoToNextFile(uf);
      if (err!=UNZ_OK) 
	  {
	    std::cerr << "Error " << err << " with zipfile in unzGoToNextFile\n";
        throw GoToNextFile_err ("Error in unzGoToNextFile !!!\n ");
      }
    }

  }
//  if (csdfile == std::string(""))
//    std::cout << "No descriptor file or too many descriptor files\n";

  unzClose(uf);
}


// This function extracts the file named filename_to_extract.
// The return value is 0 if no error.

int Unzip::extract(std::string filename_to_extract) 
{
  unzFile uf = unzOpen(_zipfilename.c_str());
  if (uf == NULL) {
//    std::cout << "Cannot open " << _zipfilename.c_str()<< " to extract the file " << filename_to_extract.c_str()<< endl;
    return(-1);
  }
  int value = do_extract_onefile(uf,filename_to_extract,0,0);

  unzClose(uf);
  return(value);
}