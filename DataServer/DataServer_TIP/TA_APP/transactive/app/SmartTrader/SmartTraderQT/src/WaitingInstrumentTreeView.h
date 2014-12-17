#ifndef __CLASS_WAITING_INSTRUMENT_TREE_VIEW_HH__
#define __CLASS_WAITING_INSTRUMENT_TREE_VIEW_HH__

#include <QtGui/QTreeView>
class CItemModelWaitingInstrument;

class CWaitingInstrumentTreeView : public QTreeView
{ 
	Q_OBJECT
public: 
	CWaitingInstrumentTreeView(QWidget* parent = 0); 
	~CWaitingInstrumentTreeView(); 
public: 
	void resetData();
private:
	CItemModelWaitingInstrument* m_pItemModelWaitingInstrument;

}; 



#endif//__CLASS_WAITING_INSTRUMENT_TREE_VIEW_HH__



