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
package ccm.request;

import org.eclipse.gef.Request;

/**
 * A request for a SimpleClassifierRolePropertiesRequest
 */
public class AddAttributeDefRequest extends Request
{
    /**
     * Creates a new SimpleClassifierRolePropertiesRequest instance.
     * @param type - the String type of this request
     */
    public AddAttributeDefRequest(String type)
    {
        super();
        setType(type);
    }
}
