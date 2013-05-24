/* 
 * File:   GraphGui.h
 * Author: fernando
 *
 * Created on 24 de Abril de 2013, 19:09
 */

#ifndef _GRAPHGUI_H
#define	_GRAPHGUI_H

#include "ui_GraphGui.h"

class GraphGui : public QMainWindow {
    Q_OBJECT
public:
    GraphGui();
    virtual ~GraphGui();
private:
    Ui::GraphGui widget;
};

#endif	/* _GRAPHGUI_H */
