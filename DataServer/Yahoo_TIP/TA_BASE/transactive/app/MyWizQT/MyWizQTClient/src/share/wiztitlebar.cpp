#include "wiztitlebar.h"

#include <QtGui/QPixmap>
#include <QtGui/QStyle>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMouseEvent>



CWizTitleBar::CWizTitleBar(QWidget *parent, QWidget* window, QWidget* shadowContainerWidget)
    : QWidget(parent)
    , m_window(window)
    , m_shadowContainerWidget(shadowContainerWidget)
    , m_oldContentsMargin(10, 10, 10, 10)
    , m_canResize(true)
{
    // 不继承父组件的背景色
    setAutoFillBackground(true);

    m_minimize = new QToolButton(this);
    m_maximize = new QToolButton(this);
    m_close = new QToolButton(this);

    // 设置按钮图像的样式    

    m_close->setFixedSize(16, 16);
    m_minimize->setFixedSize(16, 16);
    m_maximize->setFixedSize(16, 16);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setText("");

    m_window->setWindowTitle("");

    connect(m_close, SIGNAL( clicked() ), m_window, SLOT(close() ) );

    connect(m_minimize, SIGNAL( clicked() ), this, SLOT(showSmall() ) );
    connect(m_maximize, SIGNAL( clicked() ), this, SLOT(showMaxRestore() ) );
    //
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
void CWizTitleBar::layoutTitleBar()
{
    QHBoxLayout *hbox = new QHBoxLayout(this);

    hbox->addWidget(m_titleLabel);
    hbox->addWidget(m_minimize);
    hbox->addWidget(m_maximize);
    hbox->addWidget(m_close);

    hbox->insertStretch(1, 500);
    hbox->setSpacing(0);
}

void CWizTitleBar::windowStateChanged()
{
    if (Qt::WindowMaximized == m_window->windowState())
    {
        m_shadowContainerWidget->setContentsMargins(0, 0, 0, 0);
        m_maximize->setStyleSheet(m_restoreStyleSheet);
    }
    else
    {
        m_shadowContainerWidget->setContentsMargins(m_oldContentsMargin);
        m_maximize->setStyleSheet(m_maxSheet);
    }
}

void CWizTitleBar::showSmall()
{
    m_window->showMinimized();
}

void CWizTitleBar::showMaxRestore()
{
    if (!m_canResize)
        return;
    //
    if (Qt::WindowMaximized == m_window->windowState()) {
        //
        m_shadowContainerWidget->setContentsMargins(m_oldContentsMargin);
        m_window->showNormal();
        //
    } else {
        //
        m_oldContentsMargin = m_shadowContainerWidget->contentsMargins();
        m_shadowContainerWidget->setContentsMargins(0, 0, 0, 0);
        m_window->showMaximized();
    }
}

void CWizTitleBar::mousePressEvent(QMouseEvent *me)
{
    m_startPos = me->globalPos();
    m_clickPos = mapTo(m_window, me->pos());
}
void CWizTitleBar::mouseMoveEvent(QMouseEvent *me)
{
    if (Qt::WindowMaximized == m_window->windowState())
        return;
    m_window->move(me->globalPos() - m_clickPos);
}

void CWizTitleBar::mouseDoubleClickEvent ( QMouseEvent * event )
{
    if (event->button() == Qt::LeftButton)
    {
        showMaxRestore();
    }
}
void CWizTitleBar::setCanResize(bool b)
{
    m_canResize = b;
    //
    m_maximize->setEnabled(b);
    m_minimize->setEnabled(b);
}
void CWizTitleBar::setText(QString title)
{
    m_titleLabel->setText(title);
}

QString CWizTitleBar::text() const
{
    return m_titleLabel->text();
}
