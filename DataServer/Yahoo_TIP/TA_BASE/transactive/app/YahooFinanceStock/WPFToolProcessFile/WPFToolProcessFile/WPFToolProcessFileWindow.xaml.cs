using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.ComponentModel;
using System.IO;

using System.Diagnostics;

namespace WPFToolProcessFile
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class WPFToolProcessFileWindow : Window
    {
        /// <summary>
        /// 
        /// </summary>
        private System.String m_strDataSrcPath = System.String.Empty;
        private System.String m_strDataDestPath = System.String.Empty;
        private System.ComponentModel.BackgroundWorker m_backgroundWorkerAnalystFile;
        private FileSystemFolder m_FileSYstemFolder;
        private ProcessFileSSSZStock m_ProcessFileSSSZStock;

        private StocksDbOper m_StocksDbOper;

        /// <summary>
        /// 
        /// </summary>
        public WPFToolProcessFileWindow()
        {
            InitializeComponent();

            ////////////////////////////////////////
            _InitializeData();
            _InitializeEvent();

            _LogTest();
        }


        /// <summary>
        /// 
        /// </summary>
        private void _InitializeData()
        {
            this.m_strDataSrcPath = "./DataSrc";
            this.m_strDataDestPath = "./DataDest";
            this.m_backgroundWorkerAnalystFile = new System.ComponentModel.BackgroundWorker();

            m_FileSYstemFolder = new FileSystemFolder();
            m_ProcessFileSSSZStock = new ProcessFileSSSZStock();

            m_StocksDbOper = new StocksDbOper();
            System.IO.File.Delete("STOCKSSQLITE_DB.db");
            m_StocksDbOper.createNewDatabase();
            m_StocksDbOper.connectToDatabase();
            m_StocksDbOper.createTable();
            m_StocksDbOper.BeginTransaction();
            m_StocksDbOper.Commit();
            //m_StocksDbOper.disConnectToDatabase();

        }//InitializeData

        /// <summary>
        /// 
        /// </summary>
        private void _InitializeEvent()
        {
            //create one thread to do work
            //register event  DoWork  RunWorkerCompleted

            this.m_backgroundWorkerAnalystFile.DoWork +=
                new System.ComponentModel.DoWorkEventHandler(this.BackgroundWorkerAnalystFile_DoWork);

            this.m_backgroundWorkerAnalystFile.RunWorkerCompleted +=
                new System.ComponentModel.RunWorkerCompletedEventHandler(this.BackgroundWorkerAnalystFile_RunWorkerCompleted);

        }//InitializeEvent

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_DoWork_Click(object sender, RoutedEventArgs e)
        {
            this.button_DoWork.IsEnabled = false;

            this.m_strDataSrcPath = this.textBox_DataSrcPath.Text;
            this.m_strDataDestPath = this.textBox_DataDestPath.Text;


            if (this.m_strDataSrcPath.Length <= 0)
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("DataSrcPath error!"));

                //MessageBox.Show("DataSrcPath error!");
                this.button_DoWork.IsEnabled = true;
                return;
            }

            if (this.m_strDataDestPath.Length <= 0)
            {

                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("DataDestPath use default value ./DataDest"));

                //MessageBox.Show("DataDestPath use default value ./DataDest");
                this.m_strDataDestPath = "./DataDest"; ;
            }

            this.m_backgroundWorkerAnalystFile.RunWorkerAsync();

        }//button_DoWork_Click




        private void BackgroundWorkerAnalystFile_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            Boolean bProcessSubDir = true;

            MessageBox.Show("begin work");

            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("begin work"));

            //CreateDirectory DstLogPath
            m_FileSYstemFolder.createDirectory(this.m_strDataDestPath);
            //this.m_strDataSrcPath = this.textBox_Path.Text;
            processFilesInPath(this.m_strDataSrcPath, this.m_strDataDestPath, bProcessSubDir);

            m_StocksDbOper.insertAllDataToDB();
            m_StocksDbOper.disConnectToDatabase();

            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("end work!"));

            MessageBox.Show("end work!");


        }//BackgroundWorkerAnalystFile_DoWork

        private void BackgroundWorkerAnalystFile_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            this.button_DoWork.IsEnabled = true;

        }//BackgroundWorkerAnalystFile_RunWorkerCompleted




        //===============================================================
        public void processFilesInPath(System.String strDataSrcPath, System.String strDataDestPath, Boolean bProcessSubDir)
        {
            System.IO.DirectoryInfo dirInfoSrcPath;
            FileInfo[] filelist = null;

            dirInfoSrcPath = new System.IO.DirectoryInfo(strDataSrcPath);
            //bDataSrcPathExists = System.IO.Directory.Exists(strDataSrcPath);
            if (false == dirInfoSrcPath.Exists)
            {
                log4net.LogManager.GetLogger("ExeLogger").Error(System.String.Format("error! processFilesInPath  DataSrcPath not Exists"));
                //MessageBox.Show("error! processFilesInPath  DataSrcPath not Exists");
                //System.String strLog = String.Format("Error: That path not exists  strPath ={0}", strPath);
                return;
            }


            m_FileSYstemFolder.createDirectory(strDataDestPath);

            filelist = dirInfoSrcPath.GetFiles("*.*");//"*.log"

            foreach (FileInfo item in filelist)
            {
                System.String strSrcFullName = item.FullName;
                System.String strSrcFileName = item.Name;
                System.String strDestFileName = System.String.Empty;
                strDestFileName = System.IO.Path.Combine(strDataDestPath, strSrcFileName);

                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("_Process strSrcFullName={0}    strDestFileName={1}", strSrcFullName, strDestFileName));
                

                processFile(strSrcFullName, strDestFileName);
            }


            if (bProcessSubDir)
            {
                foreach (DirectoryInfo subDi in dirInfoSrcPath.GetDirectories())
                {
                    System.String strDataSrcSubPath = System.String.Empty;
                    System.String strDataDestSubPath = System.String.Empty;

                    strDataSrcSubPath = subDi.FullName;
                    strDataDestSubPath = System.IO.Path.Combine(strDataDestPath, subDi.Name);

                    processFilesInPath(strDataSrcSubPath, strDataDestSubPath, bProcessSubDir);
                }

            }
        }//processFilesInPath

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            m_ProcessFileSSSZStock.processFile(m_StocksDbOper, strDataSrcFile, strDataDestFile);

        }//processFile

        //===============================================================







        private void _LogTest()
        {
            //Trace|Debug|Info|Warn|Error|Fatal
            {
                System.Diagnostics.StackTrace StackTraceTmp = new System.Diagnostics.StackTrace(true);
                System.Diagnostics.StackFrame StackFrameTmp = null;
                int count = StackTraceTmp.FrameCount;
                for (int i = 0; i < count; i++)
                {
                    StackFrameTmp = StackTraceTmp.GetFrame(i);
                    //Console.WriteLine(StackFrameTmp.ToString() + StackFrameTmp.GetFileLineNumber() + StackFrameTmp.GetFileName());

                    //NLog.LogManager.GetCurrentClassLogger().Trace("StackFrameTmp.ToString={0}  StackFrameTmp.GetFileName={1}  StackFrameTmp.GetFileLineNumber={2}", 
                     //   StackFrameTmp.ToString(), StackFrameTmp.GetFileName(), StackFrameTmp.GetFileLineNumber());
                }
            }
            // <!--None,Fatal,ERROR,WARN,DEBUG,INFO,ALL-->
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("Info"));
            log4net.LogManager.GetLogger("ExeLogger").Debug(System.String.Format("Debug"));
            log4net.LogManager.GetLogger("ExeLogger").Warn(System.String.Format("Warn"));
            log4net.LogManager.GetLogger("ExeLogger").Error(System.String.Format("Error"));
            //log4net.LogManager.GetLogger("Fatal").Fatal(System.String.Format("Fatal"));

        }


    }//class ToolChangeSqlObjectWindow

}//namespace WPFToolProcessFile
