/*-------------------------------------------------------------------------
	    Copyright 2013 Damage Control Engineering, LLC

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*-------------------------------------------------------------------------*/
/*!
 \file DcImgLabel.h
 \brief A QLabel class that will emit a "clicked()" signal when clicked.
 It also scales the label image by -2 pixels while the mouse is pressed
 and restores the image to is original dims when released.
--------------------------------------------------------------------------*/
#ifndef DCIMGLABEL_H
#define DCIMGLABEL_H

#include <QLabel>
#include <QString>

class DcImgLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DcImgLabel(QWidget *parent = 0);
    
    void setNormalImgName( const QString& resPath );
    void setHoverImgName( const QString& resPath );


signals:
    void clicked();
    void fileDropped( const QString& path );
    void mouseMoved();
    void on_leave();
    void on_enter();

public slots:

protected:

    void mousePressEvent(QMouseEvent * ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    int _orgW, _orgH;

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    virtual void mouseMoveEvent( QMouseEvent * );
    virtual void enterEvent( QEvent * );
    virtual void leaveEvent( QEvent * );
    
    QString _hoverImageName;

    QString _normalImagename;

    // Debug
    int enterCnt;
};

#endif // DCIMGLABEL_H
