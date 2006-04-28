/*******************************************************************************
 * Copyright (c) 2000, 2005 IBM Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *     IBM Corporation - initial API and implementation
 *******************************************************************************/
package ccm.dragndrop;

import org.eclipse.gef.requests.CreationFactory;

public class DropFactory implements CreationFactory {
	
	private Object template;
	
	public DropFactory(Object str) {
		template = str;
	}
	
	public Object getNewObject() {
		return template;
	}
	
	public Object getObjectType() {
		return template.getClass();
	}
}

