
package ccm.model;


import org.eclipse.emf.common.notify.impl.NotificationImpl;


/**
 * An implementation an Ecore-specific notification.
 * @author eduardw
 */
public class CCMNotificationImpl extends NotificationImpl
{
  protected Object notifier;
  protected int featureID = NO_FEATURE_ID;
  protected int feature = -1;

  public static final int OPERATION_DEF=100;
  public static final int MODULE_DEF=101;
  public static final int INTERFACE_DEF=102;
  public static final int COMPONENT_DEF=103;
  public static final int HOME_DEF=104;
  public static final int OP_PARAMETERS=105;
  public static final int PARAMETER_DEF=106;
  public static final int TYPEDEF_DEF=107;
  public static final int CONSTANT_DEF=108;
  public static final int ATTRIBUTE_DEF=109;
  public static final int STRUCT_DEF=110;
  public static final int FIELD=111;
  public static final int ST_FIELD=112;
  public static final int UNION_DEF=113;
  public static final int UNION_FIELD=114;
  public static final int UN_UN_FIELD=115;
  public static final int EXCEPTION_DEF=116;
  public static final int EXCEP_FIELD=117;
  public static final int VALUE_DEF=118;
  public static final int CONTAINED=119;
  public static final int CONN_DEC=120;
  //********************************************
  public static final int HOMEIMPL=121;
  public static final int HOMEIINSTANCE=122;
  public static final int COMPONENTIMPL=123;
  public static final int COMPONENTINSTACE=124;
public static final int PROCESSCOLLOCATION = 135;
  public static final int COMPOSITION=125;

  public static final int EXTERNALINSTANCE=126;
public static final int RegisterComponentInstance = 134;
  public static final int CONNECTION=127;
  public static final int DeploymentUnit=128;
  public static final int Assembly=129;
  public static final int DependentFile=130;
  public static final int ContainedFile=131;
  public static final int SoftwarePackage=132;
  public static final int Property = 133;
public static final int DEPENDENTFILE = 136;
public static final int CONTAINEDFILE = 137;
  public CCMNotificationImpl(Object notifier, int eventType, int feature, Object oldValue, Object newValue, int position)
  {
    super(eventType, oldValue, newValue, position);
    this.notifier = notifier;
    this.feature = feature;
  }

  public Object getNotifier(){
    return notifier;
  }


  public int getFeatureID(Class expectedClass){
	  return feature;
  }

}

