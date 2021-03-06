import QtQuick 2.0
import QtQml.Models 2.1

// 使用Screen引入这个模块 QtQuick.Window 2.1

// 添加其他qml文件路径
import "./content"


Rectangle
{
    //0
    id: id_qml_QtQuickFinancialEye;
    //1
    width: 256;
    height: 400;


    //////////////////////////////////////////
    //data
    TotalStockListModel
    {
        id:m_TotalStockListModel
    }


    CurrentUserStockData
    {
        //
        id:m_CurrentUserStockData;
        //
        //no width height
        onSignalHistoryDataReady:
        {
            m_CurrentUserStockData.m_bool_HistoryDataReady = true;
            m_Mainpage_ListView.fun_update();
        }
    }


    //data
    PageListData
    {
        id:m_PageListData;
    }


    //data
    SqliteDbStorage
    {
        id:m_SqliteDbStorage
    }

    //data
    YahooRealTimeReqAck
    {
        id: m_YahooRealTimeReqAck;//这些都是全局变量
    }


    //data
    YahooHistoryReqAck
    {
        id: m_YahooHistoryReqAck;//这些都是全局变量
    }
    //////////////////////////////////////////



    //////////////////////////////////////////
    //UI
    //导航栏
    TopBanner
    {
        //0
        id:m_TopBanner;
        //1
        width: id_qml_QtQuickFinancialEye.width;
        height: id_qml_QtQuickFinancialEye.height * (20/400);
        anchors.top: id_qml_QtQuickFinancialEye.top
        //anchors.bottom:
    }

    //水平方向上的多个页面
    PageListView
    {
        //0
        id:m_Mainpage_ListView;
        //1
        width: id_qml_QtQuickFinancialEye.width;
        height: id_qml_QtQuickFinancialEye.height * (360/400);
        //notice:大小位置必须制定清楚才能看到滑动效果
        anchors.top: m_TopBanner.bottom;
        //anchors.bottom: m_BottomBanner.top;
        //
        onSignalUpdateCurrentUserStockData:
        {
            //emit signal signalUpdateStockInfo
            console.log('QtQuickFinancialEye.qml',
                        ' ','PageListView onSignalUpdateCurrentUserStockData',
                        ' ','slot signalUpdateCurrentUserStockData');

            m_CurrentUserStockData.fun_Update_RealTimeInfo_Current();
            m_CurrentUserStockData.fun_Update_HistoryInfo_Current();

        }
    }

    BottomBanner
    {
        id:m_BottomBanner

        //1
        width: id_qml_QtQuickFinancialEye.width;
        height: id_qml_QtQuickFinancialEye.height * (20/400);
        anchors.top: m_Mainpage_ListView.bottom
        //anchors.bottom:id_qml_QtQuickFinancialEye.bottom
    }

    //UI
    /////////////////////////////////////////////
}//Rectangle


