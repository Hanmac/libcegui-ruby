#ifndef __RubyCeguiWindow_H__
#define __RubyCeguiWindow_H__

#include "main.hpp"
void Init_CeguiWindow(VALUE rb_mCegui);

#include "ceguiwindowimpl.hpp"

#include "ceguiexception.hpp"

#include "ceguitooltip.hpp"
#include "ceguilistbox.hpp"
#include "ceguiscrollbar.hpp"
#include "ceguiitementry.hpp"
#include "ceguibuttonbase.hpp"

#include "ceguiitemlistbase.hpp"

#include "ceguieditbox.hpp"
#include "ceguimultilineeditbox.hpp"
#include "ceguicombobox.hpp"

#include "ceguigroupbox.hpp"

#include "ceguitree.hpp"

#include "ceguislider.hpp"
#include "ceguispinner.hpp"
#include "ceguiprogressbar.hpp"

#include "ceguitabcontrol.hpp"
#include "ceguilistheader.hpp"
#include "ceguilistheadersegment.hpp"

#include "ceguilayoutcontainer.hpp"

#include "ceguiclippedcontainer.hpp"
#include "ceguiscrolledcontainer.hpp"
#include "ceguidragcontainer.hpp"

#include "ceguimulticolumnlist.hpp"

#include "ceguidefaultwindow.hpp"
#include "ceguiframewindow.hpp"
template <>
inline VALUE wrap< CEGUI::Window >(CEGUI::Window *window )
{
	if(window==NULL)
		return Qnil;

	CEGUI::Tooltip *tooltip = dynamic_cast<CEGUI::Tooltip*>(window);
	if(tooltip)
		return wrap(tooltip);
	CEGUI::Listbox *listbox = dynamic_cast<CEGUI::Listbox*>(window);
	if(listbox)
		return wrap(listbox);
	CEGUI::Scrollbar *scrollbar = dynamic_cast<CEGUI::Scrollbar*>(window);
	if(scrollbar)
		return wrap(scrollbar);
	CEGUI::ItemEntry *itementry = dynamic_cast<CEGUI::ItemEntry*>(window);
	if(itementry)
		return wrap(itementry);

	CEGUI::ButtonBase *buttonbase = dynamic_cast<CEGUI::ButtonBase*>(window);
	if(buttonbase)
		return wrap(buttonbase);
	CEGUI::ItemListBase *itemlistbase = dynamic_cast<CEGUI::ItemListBase*>(window);
	if(itemlistbase)
		return wrap(itemlistbase);

	CEGUI::Editbox *editbox = dynamic_cast<CEGUI::Editbox*>(window);
		if(editbox)
			return wrap(editbox);

	CEGUI::MultiLineEditbox *multilineeditbox = dynamic_cast<CEGUI::MultiLineEditbox*>(window);
		if(multilineeditbox)
			return wrap(multilineeditbox);

	CEGUI::Combobox *combobox = dynamic_cast<CEGUI::Combobox*>(window);
		if(combobox)
			return wrap(combobox);

	CEGUI::GroupBox *groupbox = dynamic_cast<CEGUI::GroupBox*>(window);
	if(groupbox)
		return wrap(groupbox);

	CEGUI::Tree *tree = dynamic_cast<CEGUI::Tree*>(window);
	if(tree)
		return wrap(tree);

	CEGUI::Slider *slider = dynamic_cast<CEGUI::Slider*>(window);
	if(slider)
		return wrap(slider);

	CEGUI::Spinner *spinner = dynamic_cast<CEGUI::Spinner*>(window);
	if(spinner)
		return wrap(spinner);

	CEGUI::MultiColumnList *multicolumnlist = dynamic_cast<CEGUI::MultiColumnList*>(window);
	if(multicolumnlist)
		return wrap(multicolumnlist);


	CEGUI::ProgressBar *progressbar = dynamic_cast<CEGUI::ProgressBar*>(window);
	if(progressbar)
		return wrap(progressbar);

	CEGUI::TabControl *tabcontrol = dynamic_cast<CEGUI::TabControl*>(window);
	if(tabcontrol)
		return wrap(tabcontrol);

	CEGUI::ListHeader *listheader = dynamic_cast<CEGUI::ListHeader*>(window);
	if(listheader)
		return wrap(listheader);

	CEGUI::ListHeaderSegment *listheadersegment = dynamic_cast<CEGUI::ListHeaderSegment*>(window);
	if(listheadersegment)
		return wrap(listheadersegment);

	CEGUI::LayoutContainer *layoutcontainer = dynamic_cast<CEGUI::LayoutContainer*>(window);
	if(layoutcontainer)
		return wrap(layoutcontainer);

	CEGUI::ClippedContainer *clippedcontainer = dynamic_cast<CEGUI::ClippedContainer*>(window);
	if(clippedcontainer)
		return wrap(clippedcontainer);

	CEGUI::ScrolledContainer *scrolledcontainer = dynamic_cast<CEGUI::ScrolledContainer*>(window);
	if(scrolledcontainer)
		return wrap(scrolledcontainer);

	CEGUI::DragContainer *dragcontainer = dynamic_cast<CEGUI::DragContainer*>(window);
	if(dragcontainer)
		return wrap(dragcontainer);


	CEGUI::DefaultWindow *defaultwindow = dynamic_cast<CEGUI::DefaultWindow*>(window);
	if(defaultwindow)
		return wrap(defaultwindow);

	CEGUI::FrameWindow *framewindow = dynamic_cast<CEGUI::FrameWindow*>(window);
	if(framewindow)
		return wrap(framewindow);

	return RubyWindowHolder::get(window,rb_cCeguiWindow);
}


template <>
inline void wrap_each<CEGUI::WindowFactory* >(CEGUI::ConstMapIterator<std::map<CEGUI::String, CEGUI::WindowFactory*, CEGUI::StringFastLessCompare> > it)
{
	for(it.toStart(); !it.isAtEnd(); ++it)
			rb_yield(wrap(it.getCurrentKey()));
}

template <>
inline VALUE wrap< CEGUI::WindowFactoryManager::AliasTargetStack >(const CEGUI::WindowFactoryManager::AliasTargetStack &stack )
{
	return wrap(stack.getActiveTarget());
}


template <>
inline VALUE wrap< CEGUI::WindowUpdateMode >(const CEGUI::WindowUpdateMode &format )
{
	return ID2SYM(rb_intern(CEGUI::PropertyHelper<CEGUI::WindowUpdateMode>::toString(format).c_str()));
}

template <>
inline CEGUI::WindowUpdateMode wrap< CEGUI::WindowUpdateMode >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::PropertyHelper<CEGUI::WindowUpdateMode>::fromString(rb_id2name(SYM2ID(result)));
}


#endif /* __RubyCeguiWindow_H__ */
