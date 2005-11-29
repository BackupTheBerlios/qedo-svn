/*******************************************************************************
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0
 * which accompanies this distribution
 * 
 *******************************************************************************/
package ccm.editors;

import org.eclipse.gef.palette.PaletteDrawer;
import org.eclipse.gef.palette.PaletteEntry;
import org.eclipse.gef.ui.palette.PaletteCustomizer;
import org.eclipse.gef.ui.palette.customize.DefaultEntryPage;
import org.eclipse.gef.ui.palette.customize.DrawerEntryPage;
import org.eclipse.gef.ui.palette.customize.EntryPage;


/**
 * PaletteCustomizer 
 * 
 * @author eduardw
 */
public class CCMPaletteCustomizer 
	extends PaletteCustomizer 
{
	
protected static final String ERROR_MESSAGE 
									= "ERROR!";
	
/**
 * @see org.eclipse.gef.ui.palette.PaletteCustomizer#getPropertiesPage(PaletteEntry)
 */
public EntryPage getPropertiesPage(PaletteEntry entry) {
	if (entry.getType().equals(PaletteDrawer.PALETTE_TYPE_DRAWER)) {
		return new CCMDrawerEntryPage();
	}
	return new CCMEntryPage();
}

/**
 * @see org.eclipse.gef.ui.palette.PaletteCustomizer#revertToSaved()
 */
public void revertToSaved() {
}


/**
 * @see org.eclipse.gef.ui.palette.PaletteCustomizer#dialogClosed(PaletteEntry)
 */
public void save() {
}

private class CCMEntryPage extends DefaultEntryPage {
	protected void handleNameChanged(String text) {
		if (text.indexOf('*') >= 0) {
			getPageContainer().showProblem(ERROR_MESSAGE);
		} else {
			super.handleNameChanged(text);
			getPageContainer().clearProblem();
		}
	}
}

private class CCMDrawerEntryPage extends DrawerEntryPage {
	protected void handleNameChanged(String text) {
		if (text.indexOf('*') >= 0) {
			getPageContainer().showProblem(ERROR_MESSAGE);
		} else {
			super.handleNameChanged(text);
			getPageContainer().clearProblem();
		}
	}
}

}
