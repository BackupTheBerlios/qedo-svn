/*
 * Created on 19.05.2005
*/
package ccm.request;

import org.eclipse.gef.Request;

/**
 * @author Holger Kinscher
 */
public class AddDiagramRequest extends Request {
	   /**
     * Creates a new AddDiagramRequest instance.
     * @param type - the String type of this request
     */
    public AddDiagramRequest(String type)
    {
        super();
        setType(type);
    }
}
