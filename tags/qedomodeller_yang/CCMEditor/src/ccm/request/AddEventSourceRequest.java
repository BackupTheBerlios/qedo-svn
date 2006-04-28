/*
 * Created on 05.02.2005
*/
package ccm.request;

import org.eclipse.gef.Request;

/**
 * @author Holger Kinscher
 */
public class AddEventSourceRequest extends Request {

    /**
     * Creates a new CollClassifierRolePropertiesRequest instance.
     * @param type - the String type of this request
     */
    public AddEventSourceRequest(String type)
    {
        super();
        setType(type);
    }
}
