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

#include "Package.h"

#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
#endif


namespace Qedo {


void 
Package::change_file_date
( const char* filename, uLong dosdate, tm_unz tmu_date )
{
#ifdef _WIN32
    HANDLE hFile;
    FILETIME ftm, ftLocal, ftCreate, ftLastAcc, ftLastWrite;

    hFile = CreateFile( filename, GENERIC_READ | GENERIC_WRITE,
        		0, NULL, OPEN_EXISTING, 0, NULL );
    GetFileTime( hFile, &ftCreate, &ftLastAcc, &ftLastWrite );
    DosDateTimeToFileTime( (WORD)( dosdate >> 16 ), (WORD)dosdate, &ftLocal );
    LocalFileTimeToFileTime( &ftLocal, &ftm );
    SetFileTime( hFile, &ftm, &ftLastAcc, &ftm );
    CloseHandle( hFile );
#else
#ifdef unix
    struct utimbuf ut;
    struct tm newdate;
    newdate.tm_sec = tmu_date.tm_sec;
    newdate.tm_min=tmu_date.tm_min;
    newdate.tm_hour=tmu_date.tm_hour;
    newdate.tm_mday=tmu_date.tm_mday;
    newdate.tm_mon=tmu_date.tm_mon;
    if ( tmu_date.tm_year > 1900 )
	{
        newdate.tm_year=tmu_date.tm_year - 1900;
	}
	else
	{
        newdate.tm_year=tmu_date.tm_year ;
	}
    newdate.tm_isdst=-1;

    ut.actime=ut.modtime=mktime(&newdate);
    utime(filename,&ut);
#endif
#endif
}


Package::Package
( std::string file )
{
    zipfilename = file;
}


std::string 
Package::getFileNameWithSuffix
( std::string suffix )
{
    std::string csdFileName( "" );

    unzFile uf = unzOpen( zipfilename.c_str() );

	// the format of the archive is not correct or the archive file does not exist
    if ( uf == NULL )
	{
        std::cerr << "Cannot open " << zipfilename.c_str() << " to find the descriptor file\n";
        return( csdFileName );
	}

    uLong i;
    unz_global_info gi;
    int err;

    err = unzGetGlobalInfo ( uf, &gi );
    if ( err != UNZ_OK )
	{
        std::cerr << "Error " << err << " with zipfile in unzGetGlobalInfo \n";
    }

    for ( i = 0 ; i < gi.number_entry ; i++ )
	{
        char filename_inzip[256];
        unz_file_info file_info;

        err = unzGetCurrentFileInfo( uf, &file_info, filename_inzip, sizeof( filename_inzip ), NULL, 0, NULL, 0 );
        if ( err != UNZ_OK )
		{
            std::cerr << "Error " << err << " with zipfile in unzGetCurrentFileInfo\n";
            break;
		}

        std::string filename( filename_inzip );
		std::string::size_type j = filename.find( suffix );
        if ( ( j >= 0 ) && ( j < filename.size() ) )
		{
            if ( csdFileName == std::string( "" ) )
			{
                csdFileName = filename;
			}
            else // A .csd file has already been found, so the string "" is returned
			{
                csdFileName = std::string( "" );
                break;
			}
		}

        if ( ( i + 1 ) < gi.number_entry )
		{
            err = unzGoToNextFile( uf );
            if ( err != UNZ_OK )
			{
                std::cerr << "Error " << err << " with zipfile in unzGoToNextFile\n";
                break;
			}
		}

	}

    unzClose( uf );
    return( csdFileName );
}


int 
Package::extractFile
( std::string source, std::string target )
{
	// open zip
	unzFile uf = unzOpen( zipfilename.c_str() );
	if ( uf == NULL )
	{
        std::cerr << "Cannot open " << zipfilename << " to extract the file " << source << std::endl;
        return( -1 );
	}

	// locate file
	int err = unzLocateFile( uf, source.c_str(), CASESENSITIVITY );
    if ( err != UNZ_OK )
	{
        std::cerr << "File " << source << " not found in the zipfile\n";
        unzClose( uf );
		return err;
	}

	// get file info
	char filename_inzip[256];
	unz_file_info file_info;
	err = unzGetCurrentFileInfo(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
	if ( err != UNZ_OK )
	{
		std::cerr  << "Error " << err << " with zipfile in unzGetCurrentFileInfo\n";
		return( err );
	}

	// allocate memory
	void* buf = (void*)malloc( WRITEBUFFERSIZE );
	if ( buf == NULL )
	{
		std::cerr << "Error allocating memory\n";
		return UNZ_INTERNALERROR;
	}

	// open file
	FILE *fout=NULL;
	err = unzOpenCurrentFile( uf );
	if ( err != UNZ_OK )
	{
		std::cerr << "Error " << err << " with zipfile in unzOpenCurrentFile\n";
		return( err );
	}

	fout = fopen( target.c_str(), "wb" );
	if ( fout == NULL )
    {
		std::cerr << "Error opening " << target << std::endl;
		return 1;
	}

	// unpack
	do
	{
		err = unzReadCurrentFile( uf, buf, WRITEBUFFERSIZE );
		if ( err < 0 )
		{
			std::cerr << "Error " << err << " with zipfile in unzReadCurrentFile\n";
			break;
		}
		if ( err > 0 )
		{
			if ( fwrite( buf, err, 1, fout ) != 1 )
			{
				std::cerr << "Error in writing extracted file\n";
				err = UNZ_ERRNO;
				break;
			}
		}
	}
	while ( err > 0 );
	fclose( fout );
      
	if ( err == UNZ_OK )
	{
		change_file_date( target.c_str(), file_info.dosDate, file_info.tmu_date );
		err = unzCloseCurrentFile( uf );
		if ( err != UNZ_OK )
		{
			std::cerr << "Error " << err << " with zipfile in unzCloseCurrentFile\n";
		}
    }
    else
	{
		unzCloseCurrentFile( uf );
	}
	
	unzClose( uf );
	free( buf );
	return err;
}


int
Package::extractFilesWithSuffix(std::string suffix, std::string destination)
{
    unzFile uf = unzOpen( zipfilename.c_str() );
    if ( uf == NULL )
	{
        std::cerr << "Cannot open " << zipfilename.c_str() << " to find the descriptor file\n";
        return( 0 );
	}

    uLong i;
    unz_global_info gi;
    int err;
    err = unzGetGlobalInfo ( uf, &gi );
    if ( err != UNZ_OK )
	{
        std::cerr << "Error " << err << " with zipfile in unzGetGlobalInfo \n";
    }

    for ( i = 0 ; i < gi.number_entry ; i++ )
	{
        char filename_inzip[256];
        unz_file_info file_info;

        err = unzGetCurrentFileInfo( uf, &file_info, filename_inzip, sizeof( filename_inzip ), NULL, 0, NULL, 0 );
        if ( err != UNZ_OK )
		{
            std::cerr << "Error " << err << " with zipfile in unzGetCurrentFileInfo\n";
            break;
		}

		std::string filename( filename_inzip );
		std::string::size_type j = filename.find( suffix );
        if ( ( j >= 0 ) && ( j < filename.size() ) )
		{
			// extract the file
			extractFile( filename, destination + filename );
		}

        if ( ( i + 1 ) < gi.number_entry )
		{
            err = unzGoToNextFile( uf );
            if ( err != UNZ_OK )
			{
                std::cerr << "Error " << err << " with zipfile in unzGoToNextFile\n";
                break;
			}
		}

	}

	unzClose( uf );
    return( err );
}


std::string
Package::getName
()
{
	return zipfilename;
}


} // namespace
