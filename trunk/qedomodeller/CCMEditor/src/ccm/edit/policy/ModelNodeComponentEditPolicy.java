/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 */
package ccm.edit.policy;

import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.ComponentEditPolicy;
import org.eclipse.gef.requests.GroupRequest;

import CCMModel.Node;
import CCMModel.View;

import ccm.commands.delete.visual.DeleteNodeCommand;


public class ModelNodeComponentEditPolicy
	extends ComponentEditPolicy {

		/**
		 * 
		 */
		public ModelNodeComponentEditPolicy() {
			super();
		}

		/* (non-Javadoc)
		 * @see org.eclipse.gef.editpolicies.ComponentEditPolicy#createDeleteCommand(org.eclipse.gef.requests.GroupRequest)
		 */
		protected Command createDeleteCommand(GroupRequest deleteRequest) {
			View parent = (View) getHost().getParent().getModel();
			Command result = null;	
			if( getHost().getModel() instanceof Node) {
				DeleteNodeCommand deleteCmd = new DeleteNodeCommand();
				deleteCmd.setView(parent);
				deleteCmd.setDelClassifier((Node) getHost().getModel());
				result = deleteCmd;
			}
		
			return result;
		}


}

