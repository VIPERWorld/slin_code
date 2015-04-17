#include "stylehelper.h"

#include <QtGui/QFontMetrics>
#include <QtGui/QTransform>
#include <QtGui/QPainter>
#include <QtGui/QTextLayout>
#include <QtGui/QApplication>
#include <QtGui/QIcon>

#include <QtCore/QSize>
#include <QtCore/QRect>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <QtCore/QDir>


#include "utils/pathresolve.h"



namespace Utils {


void StyleHelper::initPainterByDevice(QPainter* p)
{
#ifdef Q_OS_MAC
    float factor = qt_mac_get_scalefactor(0); // factor == 2 on retina

    QTransform trans;
    trans.scale(factor, factor);
    p->setWorldTransform(trans);
#endif
}

QPixmap StyleHelper::pixmapFromDevice(const QSize& sz)
{
#ifdef Q_OS_MAC
    float factor = qt_mac_get_scalefactor(0); // factor == 2 on retina
    QSize sz2 = sz * factor;
#else
    QSize sz2 = sz;
#endif

    return QPixmap(sz2);
}

QString StyleHelper::themeName()
{
	QString strTheme = "default";
    return strTheme;
}

QString StyleHelper::skinResourceFileName(const QString& strName)
{
	QString strCurrentPath;
	QString strDefaultSkinPath;
	QString strSkinResourceFileName;
	strCurrentPath = QDir::currentPath();
	strDefaultSkinPath = strCurrentPath + "/share/skins/default";
	strSkinResourceFileName = strDefaultSkinPath + "/" + strName + ".png";
    //return ::WizGetSkinResourceFileName(themeName(), strName);
	return strSkinResourceFileName;
}

QIcon StyleHelper::loadIcon(const QString& strName)
{
    QString strThemeName = themeName();
    QString strIconNormal = skinResourceFileName(strName);
    QString strIconActive1 = skinResourceFileName(strName+ "_on");
    QString strIconActive2 = skinResourceFileName(strName+ "_selected");

    if (!QFile::exists(strIconNormal)) {
        qDebug() << "load icon failed, filePath:" << strIconNormal;
        return QIcon();
    }

    QIcon icon;
    icon.addFile(strIconNormal, QSize(), QIcon::Normal, QIcon::Off);

    // used for check state
    if (QFile::exists(strIconActive1)) {
        icon.addFile(strIconActive1, QSize(), QIcon::Active, QIcon::On);
    }

    // used for sunken state
    if (QFile::exists(strIconActive2)) {
        icon.addFile(strIconActive2, QSize(), QIcon::Active, QIcon::Off);
    }

    return icon;
}

int StyleHelper::treeViewItemHeight()
{
    return 31;
}

QColor StyleHelper::treeViewBackground()
{
    return QColor();
}

QColor StyleHelper::treeViewItemBackground(int stat)
{
    return QColor();
}

QColor StyleHelper::treeViewItemCategoryBackground()
{
    QColor co;
    co.setAlpha(15);
    return co;
}

QColor StyleHelper::treeViewItemCategoryText()
{
    return QColor();
}
QColor StyleHelper::treeViewItemLinkText()
{
    return QColor();
}

QColor StyleHelper::treeViewItemBottomLine()
{
    return QColor();
}

QColor StyleHelper::treeViewItemMessageBackground()
{
    return QColor();
}

QColor StyleHelper::treeViewItemMessageText()
{
    return QColor();
}

QColor StyleHelper::treeViewItemText(bool bSelected)
{
	return QColor();
}

QColor StyleHelper::treeViewItemTextExtend(bool bSelected)
{
	return QColor();
}

void StyleHelper::drawTreeViewItemBackground(QPainter* p, const QRect& rc, bool bFocused)
{
    QRect rcd(rc);
    QColor bg1 = treeViewItemBackground(Active);
    QColor bg2 = treeViewItemBackground(Selected);

    p->save();
    if (bFocused) {
        p->fillRect(rcd, bg1);
    } else {
        p->fillRect(rcd, bg2);
    }
    p->restore();
}

void StyleHelper::drawTreeViewItemIcon(QPainter* p, const QRect& rc, const QIcon& icn, bool bSelected)
{
    if (bSelected) {
        icn.paint(p, rc, Qt::AlignCenter, QIcon::Selected);
    } else {
        icn.paint(p, rc, Qt::AlignCenter, QIcon::Normal);
    }
}

void StyleHelper::drawTreeViewBadge(QPainter* p, const QRect& rc, const QString& str)
{
    QFont f;
    f.setPixelSize(11);
    QRect rcd(rc.adjusted(2, 2, -5, -2));
    int nWidth = QFontMetrics(f).width(str);
    int nHeight = QFontMetrics(f).height();
    if (nWidth > rcd.width() || nHeight > rcd.height()) {
        qDebug() << "[WARNING] not enough space for drawing badge string";
    }

    nWidth = (nWidth < rcd.height()) ? rcd.height() : nWidth;

    p->save();

    QColor co = treeViewItemBackground(Active);
    rcd.setLeft(rcd.right() - nWidth);
    p->setRenderHints(QPainter::Antialiasing);
    p->setBrush(co);
    p->setPen(co);
    p->drawEllipse(rcd);

    p->setPen(Qt::white);
    p->drawText(rcd, Qt::AlignCenter, str);

    p->restore();
}

int StyleHelper::listViewSortControlWidgetHeight()
{
	return 10;
}

int StyleHelper::listViewItemHeight(int nType)
{
    QFont f;
    switch (nType) {
    case ListTypeOneLine:
        return fontHead(f) + margin() * 4;
    case ListTypeTwoLine:
        return fontHead(f) + fontNormal(f) + margin() * 5;
    case ListTypeThumb:
        return thumbnailHeight() + margin() * 2;
    default:
        Q_ASSERT(0);
        return 0;
    }
}


QColor StyleHelper::listViewBackground()
{
	return QColor();
    
}

QColor StyleHelper::listViewItemSeperator()
{
	return QColor();
}

QColor StyleHelper::listViewItemBackground(int stat)
{
	return QColor();

}

QColor StyleHelper::listViewItemTitle(bool bSelected, bool bFocused)
{
	return QColor();

}

QColor StyleHelper::listViewItemLead(bool bSelected, bool bFocused)
{
	return QColor();
}

QColor StyleHelper::listViewItemSummary(bool bSelected, bool bFocused)
{
	return QColor();
}

QColor StyleHelper::listViewMultiLineFirstLine(bool bSelected)
{
	return QColor();

}

QColor StyleHelper::listViewMultiLineOtherLine(bool bSelected)
{
	return QColor();

}

QIcon StyleHelper::listViewBadge(int type)
{
    switch (type) {
    case BadgeNormal:
        return loadIcon("document_badge");
        break;
    case BadgeEncryted:
        return loadIcon("document_badge_encrypted");
        break;
    case BadgeAlwaysOnTop:
        return loadIcon("document_badge_onTop");
        break;
    default:
        break;
    }

    return QIcon();
}

void StyleHelper::drawListViewItemBackground(QPainter* p, const QRect& rc, bool bFocus, bool bSelect)
{
    QRect rcBg = rc;
    rcBg.setHeight(rcBg.height() - 1);
    if (bSelect) {
        if (bFocus) {
            p->fillRect(rcBg, listViewItemBackground(Active));
        } else {
            p->fillRect(rcBg, listViewItemBackground(Normal));
        }
    }
}

void StyleHelper::drawListViewItemBackground(QPainter* p, const QRect& rc, StyleHelper::ListViewBGType bgType)
{
    QRect rcBg = rc;
    switch (bgType) {
    case ListBGTypeNone:
        //p->fillRect(rcBg, listViewItemBackground(Normal));
        break;
    case ListBGTypeActive:
        p->fillRect(rcBg, listViewItemBackground(Active));
        break;
    case ListBGTypeHalfActive:
        p->fillRect(rcBg, listViewItemBackground(Normal));
        break;
    case ListBGTypeUnread:
        p->fillRect(rcBg, QColor("#edf0ec"));
        break;
    default:
        break;
    }

}

void StyleHelper::drawListViewItemSeperator(QPainter* p, const QRect& rc, ListViewBGType bgType)
{
    QRect rcLine = rc;
    p->save();

    switch (bgType) {
    case ListBGTypeActive:
    case ListBGTypeHalfActive:
        p->setPen(QColor("#d2d8d6"));
    case ListBGTypeUnread:
    case ListBGTypeNone:
    default:
        p->setPen(listViewItemSeperator());
        break;
    }
    p->drawLine(rcLine.bottomLeft(), rcLine.bottomRight());
    p->restore();
}

QSize StyleHelper::avatarSize()
{
    return QSize(avatarHeight(), avatarHeight());
}

int StyleHelper::avatarHeight()
{
    QFont f;
    return fontHead(f) + fontNormal(f) + margin() * 3;
}

QRect StyleHelper::drawAvatar(QPainter* p, const QRect& rc, const QPixmap& pm)
{
    QRect rectAvatar = rc;
    rectAvatar.setSize(avatarSize());

    p->save();
    p->setRenderHint(QPainter::Antialiasing);
    p->drawPixmap(rectAvatar, pm);
    p->restore();

    return rectAvatar;
}
int StyleHelper::drawSingleLineText(QPainter* p, const QRect& rc, QString& str, int nFlags, const QColor& color, const QFont& font)
{
    QPen oldpen = p->pen();
    QFont oldFont = p->font();
    //
    p->setPen(color);
    p->setFont(font);
    QRect out;
    p->drawText(rc, nFlags | Qt::TextSingleLine, str, &out);
    //
    p->setPen(oldpen);
    p->setFont(oldFont);
    //
    return out.right();
}

void StyleHelper::drawListViewItemSeperator(QPainter* p, const QRect& rc)
{
    QRect rcLine = rc;
    //rcLine.adjust(1, 0, -1, 0);
    p->save();
    p->setPen(listViewItemSeperator());
    p->drawLine(rcLine.bottomLeft(), rcLine.bottomRight());
    p->restore();
}

QRect StyleHelper::drawText(QPainter* p, const QRect& rc, QString& str, int nLines,
                          int nFlags, const QColor& color, const QFont& font, bool bElided)
{
    if (str.isEmpty()) {
        qDebug() << "[WARNING]: the text should not be empty when drawing!";
        return QRect();
    }

    QFontMetrics fm(font);
    if (rc.height() < (fm.height() + fm.leading()) * nLines) {
        qDebug() << "[WARNING]: space is not enough for drawing! text: " << str.left(30) << "...";
    }

    //if (rc.width() * nLines < fm.width(str)) {
    //    qDebug() << "[WARNING]: width should bigger than font metrics when drawing! text:" << str.left(30) << "...";
    //}

    p->save();
    p->setPen(color);
    p->setFont(font);

    int nWidth = 0;
    int nHeight = 0;
    int nHeightLine = p->fontMetrics().height() + leading();

    QRect rcRet(rc.x(), rc.y(), rc.width(), nHeightLine);
    rcRet.adjust(margin(), 0, -margin(), 0);

    QTextLayout textLayout(str, p->font());
    QTextOption opt = textLayout.textOption();
    opt.setWrapMode(QTextOption::WrapAnywhere);
    textLayout.setTextOption(opt);

    textLayout.beginLayout();
    while (nLines) {
        QTextLine line = textLayout.createLine();
        if (!line.isValid()) {
            break;
        }

        line.setLineWidth(rcRet.width());

        QString lineText;
        if (nLines == 1 && bElided) { // the last line
            lineText = p->fontMetrics().elidedText(str, Qt::ElideRight, rcRet.width());
            nWidth = qMax<int>(p->fontMetrics().width(lineText), nWidth);
        } else {
            lineText = str.left(line.textLength());
            nWidth = qMax<int>(line.width(), nWidth);
        }

        str.remove(0, line.textLength());
        p->drawText(rcRet, nFlags, lineText);

        nHeight += nHeightLine;
        rcRet.setRect(rc.x(), rc.y() + nHeight, nWidth, nHeightLine);
        rcRet.adjust(margin(), 0, -margin(), 0);

        nLines--;
    }
    textLayout.endLayout();

    rcRet.setRect(rc.x() + margin(), rc.y(), nWidth + margin(), nHeight);
    //rcRet.adjust(margin(), 0, -margin(), 0);

    p->restore();

    return rcRet;
}

QRect StyleHelper::drawThumbnailPixmap(QPainter* p, const QRect& rc, const QPixmap& pm)
{
    if (pm.isNull()) {
        qDebug() << "[WARNING]pixmap is null when drawing thumbnail";
        return QRect(rc.x(), rc.y(), 0, 0);
    }

    QRect rcd = rc.adjusted(rc.width() - rc.height(), margin(), -margin(), -margin());

    int nWidth = 0, nHeight = 0;
    if (pm.width() > rcd.width() || pm.height() > rcd.height()) {
        double fRate = qMin<double>(double(rcd.width()) / pm.width(), double(rcd.height()) / pm.height());
        nWidth = int(pm.width() * fRate);
        nHeight = int(pm.height() * fRate);
    } else {
        nWidth = pm.width();
        nHeight = pm.height();
    }

    int adjustX = (rcd.width() - nWidth) / 2;
    int adjustY = (rcd.height() - nHeight) / 2;
    rcd.adjust(adjustX, adjustY, -adjustX, -adjustY);
    p->drawPixmap(rcd, pm);

    return rcd;
}

QRect StyleHelper::drawBadgeIcon(QPainter* p, const QRect& rc, int height, int type, bool bFocus, bool bSelect)
{
    QIcon badge(listViewBadge(type));
    QRect rcb = rc.adjusted(margin(), margin(), 0, 0);
    rcb.setSize(QSize(height, height));
    if (bSelect && bFocus) {
        badge.paint(p, rcb, Qt::AlignBottom, QIcon::Active, QIcon::Off);
    } else {
        badge.paint(p, rcb, Qt::AlignBottom, QIcon::Normal, QIcon::Off);
    }

    return rcb;
}

QRect StyleHelper::drawAttachIcon(QPainter* p, const QRect& rc, bool bFocus, bool bSelect)
{
    QIcon attachIcon(loadIcon("document_containsattach"));
    QSize iconSize = rc.size();
    int nLeftMargin = 2;
    QRect rcb = rc.adjusted(nLeftMargin, margin(), 0, 0);
    rcb.setSize(iconSize);
    if (bSelect && bFocus) {
        attachIcon.paint(p, rcb, Qt::AlignTop, QIcon::Active, QIcon::On);
    } else {
        attachIcon.paint(p, rcb, Qt::AlignTop, QIcon::Normal, QIcon::Off);
    }

    return rcb;
}

int StyleHelper::lineSpacing()
{
    return 5;
}

int StyleHelper::leading()
{
    return 3;
}

int StyleHelper::margin()
{
    return 5;
}

int StyleHelper::thumbnailHeight()
{
    QFont f;
    return fontHead(f) + fontNormal(f) * 3 + margin() * 5;
}

QPolygon StyleHelper::bubbleFromSize(const QSize& sz, int nAngle, bool bAlignLeft)
{
    Q_ASSERT(sz.width() > 31);
    Q_ASSERT(sz.height() > 11);

    QVector<QPoint> ps;
    if (bAlignLeft) {
        ps.push_back(QPoint(0, nAngle));
        ps.push_back(QPoint(11, nAngle));
        ps.push_back(QPoint(11 + nAngle, 0));
        ps.push_back(QPoint(11 + nAngle * 2, nAngle));
        ps.push_back(QPoint(sz.width(), nAngle));
        ps.push_back(QPoint(sz.width(), sz.height()));
        ps.push_back(QPoint(0, sz.height()));
    } else {
        ps.push_back(QPoint(1, 10));
        ps.push_back(QPoint(sz.width() - 11 - nAngle * 2, nAngle));
        ps.push_back(QPoint(sz.width() - 11 - nAngle, 0));
        ps.push_back(QPoint(sz.width() - 11, nAngle));
        ps.push_back(QPoint(sz.width() - 1, nAngle));
        ps.push_back(QPoint(sz.width(), nAngle + 1));
        ps.push_back(QPoint(sz.width(), sz.height()));
        ps.push_back(QPoint(0, sz.height()));
        ps.push_back(QPoint(0, nAngle + 1));
    }

    return QPolygon(ps);
}

int StyleHelper::fontHead(QFont& f)
{

#ifdef Q_OS_MAC
//    QSettings* st = ExtensionSystem::PluginManager::settings();
//    QString strFont = st->value("Theme/FontFamily").toString();
//    if (strFont.isEmpty()) {
//        st->setValue("Theme/FontFamily", f.family());
//    }

    //f.setFamily(strFont);
    //FIXME: should not use fix font size. but different widget has different default font size.
    f.setPixelSize(13);
    //f.setBold(true);
#endif

    return QFontMetrics(f).height();
}

int StyleHelper::fontNormal(QFont& f)
{
#ifdef Q_OS_MAC
//    QSettings* st = ExtensionSystem::PluginManager::settings();
//    QString strFont = st->value("Theme/FontFamily").toString();
//    if (strFont.isEmpty()) {
//        st->setValue("Theme/FontFamily", f.family());
//    }

//    f.setFamily(strFont);
    //FIXME: should not use fix font size. but different widget has different default font size.
    f.setPixelSize(13);
#endif
    return QFontMetrics(f).height();
}

int StyleHelper::fontExtend(QFont& f)
{
    QString strFont;
    f.setFamily(strFont);
    f.setPixelSize(9);

    return QFontMetrics(f).height();
}

int StyleHelper::titleEditorHeight()
{
    return 30;
}

int StyleHelper::editToolBarHeight()
{
    return 30;
}

int StyleHelper::notifyBarHeight()
{
    return 32;
}

QRect StyleHelper::initListViewItemPainter(QPainter* p, const QRect& lrc, ListViewBGType bgType)
{
    QRect rc = lrc;

    Utils::StyleHelper::drawListViewItemBackground(p, rc, bgType);

    Utils::StyleHelper::drawListViewItemSeperator(p, rc, bgType);

    int nMargin = Utils::StyleHelper::margin();
    return rc.adjusted(nMargin, nMargin, -nMargin, -nMargin);
}

void StyleHelper::drawListViewItemThumb(QPainter* p, const QRect& rc, int nBadgeType,
                                        const QString& title, const QString& lead, const QString& abs,
                                        bool bFocused, bool bSelected, bool bContainsAttach)
{
    QRect rcd(rc);

    QFont fontTitle = p->font();
    int nFontHeight = Utils::StyleHelper::fontHead(fontTitle);

    if (!title.isEmpty()) {
        QRect rcTitle = Utils::StyleHelper::drawBadgeIcon(p, rcd, nFontHeight, nBadgeType, bFocused, bSelected);

        int nSpace4AttachIcon = 20;
        rcTitle.setCoords(rcTitle.right(), rcTitle.y(), rcd.right() - nSpace4AttachIcon, rcd.bottom());
        QString strTitle(title);
        QColor colorTitle = Utils::StyleHelper::listViewItemTitle(bSelected, bFocused);
        QRect rcAttach = Utils::StyleHelper::drawText(p, rcTitle, strTitle, 1, Qt::AlignVCenter, colorTitle, fontTitle);

        if (bContainsAttach) {
            rcAttach.setCoords(rcAttach.right(), rcd.top(), rcd.right(), rcTitle.bottom());
            rcAttach.setHeight(nFontHeight);
            Utils::StyleHelper::drawAttachIcon(p, rcAttach, bFocused, bSelected);
        }

        rcd.adjust(0, rcAttach.height() + margin(), 0, 0);
    }

    QFont fontThumb;
    nFontHeight = Utils::StyleHelper::fontNormal(fontThumb);

    QRect rcLead;
    if (!lead.isEmpty()) {
        QString strInfo(lead);
        QColor colorDate = Utils::StyleHelper::listViewItemLead(bSelected, bFocused);
        rcLead = Utils::StyleHelper::drawText(p, rcd, strInfo, 1, Qt::AlignVCenter, colorDate, fontThumb);
    }

    if (!abs.isEmpty()) {
        QString strText(abs);
        QRect rcLine1(rcd.adjusted(rcLead.width(), 0, 0, 0));
        QColor colorSummary = Utils::StyleHelper::listViewItemSummary(bSelected, bFocused);
        rcLine1 = Utils::StyleHelper::drawText(p, rcLine1, strText, 1, Qt::AlignVCenter, colorSummary, fontThumb, false);

        if (!strText.isEmpty()) {
            QRect rcLine2(rcd.adjusted(0, rcLine1.height(), 0, 0));
            rcLine2 = Utils::StyleHelper::drawText(p, rcLine2, strText, 2, Qt::AlignVCenter, colorSummary, fontThumb);
        }
    }
}


} // namespace Utils
