/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 * 
 */
package ccm.editors.tools;


import org.eclipse.gef.commands.Command;
import org.eclipse.gef.requests.CreationFactory;
import org.eclipse.gef.tools.CreationTool;
import org.eclipse.swt.widgets.Shell;

import ccm.commands.create.visual.CreateNodeForAliasDefCommand;
import ccm.commands.create.visual.CreateNodeForAssemblyCommand;
import ccm.commands.create.visual.CreateNodeForComponentDefCommand;
import ccm.commands.create.visual.CreateNodeForComponentImplCommand;
import ccm.commands.create.visual.CreateNodeForCompositionCommand;
import ccm.commands.create.visual.CreateNodeForConstantDefCommand;
import ccm.commands.create.visual.CreateNodeForDeploymentUnitCommand;
import ccm.commands.create.visual.CreateNodeForEnumDefCommand;
import ccm.commands.create.visual.CreateNodeForExceptionDefCommand;
import ccm.commands.create.visual.CreateNodeForExternalInstanceCommand;
import ccm.commands.create.visual.CreateNodeForHomeDefCommand;
import ccm.commands.create.visual.CreateNodeForHomeImplCommand;
import ccm.commands.create.visual.CreateNodeForHomeInstanceCommand;
import ccm.commands.create.visual.CreateNodeForInterfaceDefCommand;
import ccm.commands.create.visual.CreateNodeForModuleDefCommand;
import ccm.commands.create.visual.CreateNodeForProcessCollocationCommand;
import ccm.commands.create.visual.CreateNodeForSoftwarePackageCommand;
import ccm.commands.create.visual.CreateNodeForStructDefCommand;
import ccm.commands.create.visual.CreateNodeForUnionDefCommand;
import ccm.commands.create.visual.CreateNodeForValueBoxDefCommand;
import ccm.commands.create.visual.CreateNodeForValueDefCommand;


public class CCMCreationTool extends CreationTool {
    
    private Execution execute= new Execution();
	/**
	 * Constructor
	 */
	public CCMCreationTool() {super();}

	
	/**
	 * 
	 * @param aFactory
	 */
	public CCMCreationTool(CreationFactory aFactory) {super(aFactory);}

	/**
	 * @see org.eclipse.gef.tools.AbstractTool#executeCurrentCommand()
	 */
	protected void executeCurrentCommand() {
		Command command=getCurrentCommand();
		Shell shell=this.getCurrentViewer().getControl().getShell();
        if(command instanceof CreateNodeForModuleDefCommand){
            if(!execute.canExecute((CreateNodeForModuleDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForHomeDefCommand){
            if(!execute.canExecute((CreateNodeForHomeDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForInterfaceDefCommand){
            if(!execute.canExecute((CreateNodeForInterfaceDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForComponentDefCommand){
            if(!execute.canExecute((CreateNodeForComponentDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForEnumDefCommand){
            if(!execute.canExecute((CreateNodeForEnumDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForValueBoxDefCommand){
            if(!execute.canExecute((CreateNodeForValueBoxDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForAliasDefCommand){
            if(!execute.canExecute((CreateNodeForAliasDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForConstantDefCommand){
            if(!execute.canExecute((CreateNodeForConstantDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForStructDefCommand){
            if(!execute.canExecute((CreateNodeForStructDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForUnionDefCommand){
            if(!execute.canExecute((CreateNodeForUnionDefCommand) command,shell))return;     
        } 
        if(command instanceof CreateNodeForExceptionDefCommand){
            if(!execute.canExecute((CreateNodeForExceptionDefCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForValueDefCommand){
            if(!execute.canExecute((CreateNodeForValueDefCommand) command,shell))return;     
        }
        //*******************************************************
        if(command instanceof CreateNodeForAssemblyCommand){
            
                if(!execute.canExecute((CreateNodeForAssemblyCommand) command,shell))return;     
            }
        if(command instanceof CreateNodeForExternalInstanceCommand){
            
                if(!execute.canExecute((CreateNodeForExternalInstanceCommand) command,shell))return;     
            }
        if(command instanceof CreateNodeForHomeInstanceCommand){
            
                if(!execute.canExecute((CreateNodeForHomeInstanceCommand) command,shell))return;     
            }
        
        if(command instanceof CreateNodeForProcessCollocationCommand){
            
                if(!execute.canExecute((CreateNodeForProcessCollocationCommand) command,shell))return;     
            }
        
        
        
        if(command instanceof CreateNodeForSoftwarePackageCommand){
            
                if(!execute.canExecute((CreateNodeForSoftwarePackageCommand) command,shell))return;     
            }
        if(command instanceof CreateNodeForDeploymentUnitCommand){
        
            if(!execute.canExecute((CreateNodeForDeploymentUnitCommand) command,shell))return;     
        }
       
        if(command instanceof CreateNodeForCompositionCommand){
        	 
            if(!execute.canExecute((CreateNodeForCompositionCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForHomeImplCommand){
        	 
            if(!execute.canExecute((CreateNodeForHomeImplCommand) command,shell))return;     
        }
        if(command instanceof CreateNodeForComponentImplCommand){
        	 
            if(!execute.canExecute((CreateNodeForComponentImplCommand) command,shell))return;     
        }
        //************************************
		super.executeCurrentCommand();
	}
}
