/*
 * Created on 07.08.2005
 *
 */
package ccm.request;

import org.eclipse.gef.Request;

/**
 * @author christian
 *
 */
public class AddFactoryRequest extends Request {

    public AddFactoryRequest(String type) {
        super();
        setType(type);
    }

}
