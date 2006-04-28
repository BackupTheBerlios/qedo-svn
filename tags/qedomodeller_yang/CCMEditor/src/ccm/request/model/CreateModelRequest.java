/*
 * Created on Jun 2, 2005
 *
 */
package ccm.request.model;

import org.eclipse.gef.Request;

/**
 * @author kinscher
 *
 */
public class CreateModelRequest extends Request {
	
	/**
     * Creates a new CreateModelRequest instance.
     * @param type - the String type of this request
     */
    public CreateModelRequest(Class type)
    {
        super();
        setType(type);
    }
}
