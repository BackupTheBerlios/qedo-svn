/*
 * Created on 05.02.2005
*/
package ccm.request;

import org.eclipse.gef.Request;

/**
 * @author Holger Kinscher
 */
public class AddEmitsSourceRequest extends Request {

    /**
     * Creates a new CollClassifierRolePropertiesRequest instance.
     * @param type - the String type of this request
     */
    public AddEmitsSourceRequest(String type)
    {
        super();
        setType(type);
    }
}
