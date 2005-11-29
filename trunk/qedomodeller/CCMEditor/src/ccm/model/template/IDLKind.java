/*
 * Created on 12.03.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.model.template;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.eclipse.emf.common.util.AbstractEnumerator;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public final class IDLKind extends AbstractEnumerator {
    /**
     * The '<em><b>IDL</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #IDL_LITERAL
     * @model 
     * @generated
     * @ordered
     */
    public static final int IDL = 0;

    /**
     * The '<em><b>PK SHORT</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #PK_SHORT_LITERAL
     * @model 
     * @generated
     * @ordered
     */
    public static final int ARRAY = 5;

    /**
     * The '<em><b>PK LONG</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #PK_LONG_LITERAL
     * @model 
     * @generated
     * @ordered
     */
    public static final int WSTRING = 1;

    /**
     * The '<em><b>PK USHORT</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #PK_USHORT_LITERAL
     * @model 
     * @generated
     * @ordered
     */
    public static final int STRING = 2;

    /**
     * The '<em><b>PK ULONG</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #PK_ULONG_LITERAL
     * @model 
     * @generated
     * @ordered
     */
    public static final int FIXED = 3;

    /**
     * The '<em><b>PK FLOAT</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #PK_FLOAT_LITERAL
     * @model 
     * @generated
     * @ordered
     */
    public static final int SEQUENCE = 4;
    
    /**
     * The '<em><b>PK VOID</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>PK VOID</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #PK_VOID
     * @generated
     * @ordered
     */
    public static final IDLKind IDL_LITERAL = new IDLKind(IDL, "IDL");

    /**
     * The '<em><b>PK SHORT</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>PK SHORT</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #PK_SHORT
     * @generated
     * @ordered
     */
    public static final IDLKind WSTRING_LITERAL = new IDLKind(WSTRING, "WSTRING");

    /**
     * The '<em><b>PK LONG</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>PK LONG</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #PK_LONG
     * @generated
     * @ordered
     */
    public static final IDLKind STRING_LITERAL = new IDLKind(STRING, "STRING");

    /**
     * The '<em><b>PK USHORT</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>PK USHORT</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #PK_USHORT
     * @generated
     * @ordered
     */
    public static final IDLKind FIXED_LITERAL = new IDLKind(FIXED, "FIXED");

    /**
     * The '<em><b>PK ULONG</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>PK ULONG</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #PK_ULONG
     * @generated
     * @ordered
     */
    public static final IDLKind ARRAY_LITERAL = new IDLKind(ARRAY, "ARRAY");

    /**
     * The '<em><b>PK FLOAT</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>PK FLOAT</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #PK_FLOAT
     * @generated
     * @ordered
     */
    public static final IDLKind SEQUENCE_LITERAL = new IDLKind(SEQUENCE, "SEQUENCE");


    /**
     * An array of all the '<em><b>Primitive Kind</b></em>' enumerators.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private static final IDLKind[] VALUES_ARRAY =
        new IDLKind[] {
            IDL_LITERAL,
            ARRAY_LITERAL,
            WSTRING_LITERAL,
            STRING_LITERAL,
            FIXED_LITERAL,
            SEQUENCE_LITERAL
        };

    /**
     * A public read-only list of all the '<em><b>Primitive Kind</b></em>' enumerators.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final List VALUES = Collections.unmodifiableList(Arrays.asList(VALUES_ARRAY));

    /**
     * Returns the '<em><b>Primitive Kind</b></em>' literal with the specified name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static IDLKind get(String name) {
        for (int i = 0; i < VALUES_ARRAY.length; ++i) {
            IDLKind result = VALUES_ARRAY[i];
            if (result.toString().equals(name)) {
                return result;
            }
        }
        return null;
    }

    /**
     * Returns the '<em><b>Primitive Kind</b></em>' literal with the specified value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static IDLKind get(int value) {
        switch (value) {
            case IDL: return IDL_LITERAL;
            case WSTRING: return WSTRING_LITERAL;
            case STRING: return STRING_LITERAL;
            case FIXED: return FIXED_LITERAL;
            case ARRAY: return ARRAY_LITERAL;
            case SEQUENCE: return SEQUENCE_LITERAL;
        }
        return null;	
    }

    /**
     * Only this class can construct instances.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private IDLKind(int value, String name) {
        super(value,name);
    }

} 
