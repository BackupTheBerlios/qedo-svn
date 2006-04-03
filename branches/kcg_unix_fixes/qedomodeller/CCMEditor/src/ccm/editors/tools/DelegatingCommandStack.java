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

import java.util.EventObject;

import org.eclipse.gef.commands.Command;
import org.eclipse.gef.commands.CommandStack;
import org.eclipse.gef.commands.CommandStackListener;
import org.eclipse.gef.commands.UnexecutableCommand;
import org.eclipse.swt.widgets.Shell;

import ccm.commands.create.model.CreateAliasDefCommand;
import ccm.commands.create.model.CreateAssemblyCommand;
import ccm.commands.create.model.CreateComponentDefCommand;
import ccm.commands.create.model.CreateComponentImplDefCommand;
import ccm.commands.create.model.CreateCompositionDefCommand;
import ccm.commands.create.model.CreateConstantDefCommand;
import ccm.commands.create.model.CreateEnumDefCommand;
import ccm.commands.create.model.CreateEventDefCommand;
import ccm.commands.create.model.CreateExceptionDefCommand;
import ccm.commands.create.model.CreateExternalInstanceCommand;
import ccm.commands.create.model.CreateHomeDefCommand;
import ccm.commands.create.model.CreateHomeImplDefCommand;
import ccm.commands.create.model.CreateHomeInstanceCommand;
import ccm.commands.create.model.CreateImplementationCommand;
import ccm.commands.create.model.CreateInterfaceDefCommand;
import ccm.commands.create.model.CreateModuleDefCommand;
import ccm.commands.create.model.CreateProcessCollocationCommand;
import ccm.commands.create.model.CreateSoftwarePackageCommand;
import ccm.commands.create.model.CreateStructDefCommand;
import ccm.commands.create.model.CreateUnionDefCommand;
import ccm.commands.create.model.CreateValueBoxDefCommand;
import ccm.commands.create.model.CreateValueDefCommand;
import ccm.commands.create.visual.CreateDiagramCommand;
import ccm.commands.create.visual.adds.AddAliasDefCommand;
import ccm.commands.create.visual.adds.AddAttributeDefCommand;
import ccm.commands.create.visual.adds.AddComponentFileCommand;
import ccm.commands.create.visual.adds.AddComponentInstanceCommand;
import ccm.commands.create.visual.adds.AddConstantDefCommand;
import ccm.commands.create.visual.adds.AddContainedFileCommand;
import ccm.commands.create.visual.adds.AddDepententFileCommand;
import ccm.commands.create.visual.adds.AddDeploymenRequirementCommand;
import ccm.commands.create.visual.adds.AddEmitsSourceCommand;
import ccm.commands.create.visual.adds.AddEnumDefCommand;
import ccm.commands.create.visual.adds.AddEventSinkCommand;
import ccm.commands.create.visual.adds.AddEventSourceCommand;
import ccm.commands.create.visual.adds.AddExceptionDefCommand;
import ccm.commands.create.visual.adds.AddFacetCommand;
import ccm.commands.create.visual.adds.AddIDLCommand;
import ccm.commands.create.visual.adds.AddOperationDefCommand;
import ccm.commands.create.visual.adds.AddPropertyCommand;
import ccm.commands.create.visual.adds.AddReceptacleCommand;
import ccm.commands.create.visual.adds.AddRegisterComponentInstanceCommand;
import ccm.commands.create.visual.adds.AddRuleCommand;
import ccm.commands.create.visual.adds.AddStructDefCommand;
import ccm.commands.create.visual.adds.AddUnionDefCommand;
import ccm.commands.create.visual.adds.AddValueBoxDefCommand;
import ccm.commands.create.visual.adds.AddValueMemberDefCommand;
import ccm.commands.edit.EditOperationCommand;

/**
 * This is a delegating command stack, which delegates everything
 * a defined the CommandStack except event listners.
 * 
 * <p>Event listeners registered to a <code>DelegatingCommandStack</code>
 * will be informed whenever the underlying <code>CommandStack</code>
 * changes. They will not be registered to the underlying
 * <code>CommandStack</code> but they will be informed about change events
 * of them.
 * 
 */
public class DelegatingCommandStack
    extends CommandStack
    implements CommandStackListener
{
    private static final Object[] EMPTY_OBJECT_ARRAY = new Object[] {};
    /** the current command stack */
    private CommandStack currentCommandStack;
    private Shell shell;
    private Execution execute=new Execution();

	/**
	 * 
	 */
	public DelegatingCommandStack(Shell shell) {
		super();
		this.shell=shell;
	}

    /**
     * Returns the current <code>CommandStack</code>.
     * @return the current <code>CommandStack</code>
     */
    public CommandStack getCurrentCommandStack(){
        return currentCommandStack;
    }

    /**
     * Sets the current <code>CommandStack</code>.
     * @param stack the <code>CommandStack</code> to set
     */
    public void setCurrentCommandStack(CommandStack stack){
        if (currentCommandStack == stack)
            return;

        // remove from old command stack
        if (null != currentCommandStack)
            currentCommandStack.removeCommandStackListener(this);

        // set new command stack
        currentCommandStack = stack;

        // watch new command stack
        currentCommandStack.addCommandStackListener(this);

        // the command stack changed
        //notifyListeners();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#canRedo()
     */
    public boolean canRedo(){
        if (null == currentCommandStack)
            return false;

        return currentCommandStack.canRedo();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#canUndo()
     */
    public boolean canUndo(){
        if (null == currentCommandStack)
            return false;

        return currentCommandStack.canUndo();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#dispose()
     */
    public void dispose(){
        if (null != currentCommandStack)
            currentCommandStack.dispose();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#execute(org.eclipse.gef.commands.Command)
     */
    public void execute(Command command){
        if (null != currentCommandStack){
        	//*****************************************
        	if(command instanceof CreateSoftwarePackageCommand){
        		  
          		if(!execute.canExecute((CreateSoftwarePackageCommand) command,shell))return;
        	    }
        	if(command instanceof CreateImplementationCommand){
        		  
          		if(!execute.canExecute((CreateImplementationCommand) command,shell))return;
        	    }
        	if(command instanceof CreateAssemblyCommand){
        		  
          		if(!execute.canExecute((CreateAssemblyCommand) command,shell))return;
        	    }
        	if(command instanceof CreateProcessCollocationCommand){
        		  
          		if(!execute.canExecute((CreateProcessCollocationCommand) command,shell))return;
        	    }
        	if(command instanceof CreateHomeInstanceCommand){
        		  
          		if(!execute.canExecute((CreateHomeInstanceCommand) command,shell))return;
        	    }
        	if(command instanceof CreateExternalInstanceCommand){
        		  
          		if(!execute.canExecute((CreateExternalInstanceCommand) command,shell))return;
        	    }
        	
        	
        	if(command instanceof  AddComponentFileCommand){
      		  
        		if(!execute.canExecute((AddComponentFileCommand) command,shell))return;
      	    }	
        	if(command instanceof  AddIDLCommand){
        		  
          		if(!execute.canExecute((AddIDLCommand) command,shell))return;
        	    }	
        	
        	
        	if(command instanceof AddComponentInstanceCommand){
      		  
        		if(!execute.canExecute((AddComponentInstanceCommand) command,shell))return;
      	    }
        	if(command instanceof AddRegisterComponentInstanceCommand){
        		  
          		if(!execute.canExecute((AddRegisterComponentInstanceCommand) command,shell))return;
        	    }
        	if(command instanceof AddRuleCommand){
        		  
          		if(!execute.canExecute((AddRuleCommand) command,shell))return;
        	    }
        	if(command instanceof AddDepententFileCommand){
        		  
          		if(!execute.canExecute((AddDepententFileCommand) command,shell))return;
        	    }
        	if(command instanceof AddPropertyCommand){
      		  
        		if(!execute.canExecute((AddPropertyCommand) command,shell))return;
      	    }
        	if(command instanceof AddContainedFileCommand){
      		  
        		if(!execute.canExecute((AddContainedFileCommand) command,shell))return;
      	    }
        	if(command instanceof AddDeploymenRequirementCommand){
      		  
        		if(!execute.canExecute((AddDeploymenRequirementCommand) command,shell))return;
      	    }
        	
        	
        	
        	
        	
        	if(command instanceof EditOperationCommand){
        		  
        		if(!execute.canExecute((EditOperationCommand) command,shell))return;
        	}
        	if(command instanceof CreateCompositionDefCommand){
      		  
      		   if(!execute.canExecute((CreateCompositionDefCommand) command,shell))return;
      	    }
        	if(command instanceof CreateComponentImplDefCommand){
        		  
        		   if(!execute.canExecute((CreateComponentImplDefCommand) command,shell))return;
        	    }
        	if(command instanceof CreateHomeImplDefCommand){
        		  
        		   if(!execute.canExecute((CreateHomeImplDefCommand) command,shell))return;
        	    }
        	//*****************************************
        	if(command instanceof AddFacetCommand){
        		if(!execute.canExecute((AddFacetCommand) command,shell))return;
        	}
        	if(command instanceof AddReceptacleCommand){
        		if(!execute.canExecute((AddReceptacleCommand) command,shell))return;
        	}
        	if(command instanceof AddEventSinkCommand){
        		if(!execute.canExecute((AddEventSinkCommand) command,shell))return;
        	}
        	if(command instanceof AddEventSourceCommand){
        		if(!execute.canExecute((AddEventSourceCommand) command,shell))return;
        	}
        	if(command instanceof AddEmitsSourceCommand){
        		if(!execute.canExecute((AddEmitsSourceCommand) command,shell))return;
        	}
            if(command instanceof AddOperationDefCommand){
                if(!execute.canExecute((AddOperationDefCommand) command,shell))return;    
            }
            if(command instanceof AddConstantDefCommand){
                if(!execute.canExecute((AddConstantDefCommand) command,shell))return; 
            }
            if(command instanceof AddValueMemberDefCommand){
                if(!execute.canExecute((AddValueMemberDefCommand) command,shell))return;     
            }
            if(command instanceof AddAttributeDefCommand){
                if(!execute.canExecute((AddAttributeDefCommand) command,shell))return;     
            }
            if(command instanceof AddUnionDefCommand){
                if(!execute.canExecute((AddUnionDefCommand) command,shell))return;     
            } 
            if(command instanceof AddStructDefCommand){
                if(!execute.canExecute((AddStructDefCommand) command,shell))return;     
            }
            if(command instanceof AddEnumDefCommand){
                if(!execute.canExecute((AddEnumDefCommand) command,shell))return;     
            }
            if(command instanceof AddAliasDefCommand){
                if(!execute.canExecute((AddAliasDefCommand) command,shell))return;     
            }
            if(command instanceof AddValueBoxDefCommand){
                if(!execute.canExecute((AddValueBoxDefCommand) command,shell))return;     
            }
            if(command instanceof AddExceptionDefCommand){
                if(!execute.canExecute((AddExceptionDefCommand) command,shell))return;     
            }
            if(command instanceof CreateDiagramCommand){
                if(!execute.canExecute((CreateDiagramCommand) command,shell))return;     
            }
            if(command instanceof CreateComponentDefCommand){
                if(!execute.canExecute((CreateComponentDefCommand) command,shell))return;     
            }
            if(command instanceof CreateModuleDefCommand){
                if(!execute.canExecute((CreateModuleDefCommand) command,shell))return;     
            }
            if(command instanceof CreateValueDefCommand){
                if(!execute.canExecute((CreateValueDefCommand) command,shell))return;     
            }
            if(command instanceof CreateConstantDefCommand){
                if(!execute.canExecute((CreateConstantDefCommand) command,shell))return;     
            }
			if(command instanceof CreateEventDefCommand){
                if(!execute.canExecute((CreateEventDefCommand) command,shell))return;     
            }
			if(command instanceof CreateValueBoxDefCommand){
                if(!execute.canExecute((CreateValueBoxDefCommand) command,shell))return;     
            }
			if(command instanceof CreateEnumDefCommand){
                if(!execute.canExecute((CreateEnumDefCommand) command,shell))return;     
            }
			if(command instanceof CreateAliasDefCommand){
                if(!execute.canExecute((CreateAliasDefCommand) command,shell))return;     
            }
			if(command instanceof CreateStructDefCommand){
                if(!execute.canExecute((CreateStructDefCommand) command,shell))return;     
            }
			if(command instanceof CreateUnionDefCommand){
                if(!execute.canExecute((CreateUnionDefCommand) command,shell))return;     
            }
            if(command instanceof CreateHomeDefCommand){
                if(!execute.canExecute((CreateHomeDefCommand) command,shell))return;     
            }
           if(command instanceof CreateInterfaceDefCommand){
                if(!execute.canExecute((CreateInterfaceDefCommand) command,shell))return;     
            }
           if(command instanceof CreateExceptionDefCommand){
            if(!execute.canExecute((CreateExceptionDefCommand) command,shell))return;     
        }
        currentCommandStack.execute(command);
        }
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#flush()
     */
    public void flush(){
        if (null != currentCommandStack)
            currentCommandStack.flush();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#getCommands()
     */
    public Object[] getCommands(){
        if (null == currentCommandStack)
            return EMPTY_OBJECT_ARRAY;

        return currentCommandStack.getCommands();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#getRedoCommand()
     */
    public Command getRedoCommand(){
        if (null == currentCommandStack)
            return UnexecutableCommand.INSTANCE;

        return currentCommandStack.getRedoCommand();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#getUndoCommand()
     */
    public Command getUndoCommand(){
        if (null == currentCommandStack)
            return UnexecutableCommand.INSTANCE;

        return currentCommandStack.getUndoCommand();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#getUndoLimit()
     */
    public int getUndoLimit(){
        if (null == currentCommandStack)
            return -1;

        return currentCommandStack.getUndoLimit();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#isDirty()
     */
    public boolean isDirty(){
        if (null == currentCommandStack)
            return false;

        return currentCommandStack.isDirty();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#markSaveLocation()
     */
    public void markSaveLocation(){
        if (null != currentCommandStack)
            currentCommandStack.markSaveLocation();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#redo()
     */
    public void redo(){
        if (null != currentCommandStack)
            currentCommandStack.redo();
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#setUndoLimit(int)
     */
    public void setUndoLimit(int undoLimit){
        if (null != currentCommandStack)
            currentCommandStack.setUndoLimit(undoLimit);
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStack#undo()
     */
    public void undo(){
        if (null != currentCommandStack)
            currentCommandStack.undo();
    }

    /* (non-Javadoc)
     * @see java.lang.Object#toString()
     */
    public String toString(){
        return "DelegatingCommandStack(" + currentCommandStack + ")";
    }

    /* (non-Javadoc)
     * @see org.eclipse.gef.commands.CommandStackListener#commandStackChanged(java.util.EventObject)
     */
    public void commandStackChanged(EventObject event){
        //notifyListeners();
    }

}
