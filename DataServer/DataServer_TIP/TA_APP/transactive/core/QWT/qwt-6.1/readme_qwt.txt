http://blog.sina.com.cn/s/blog_a6fb6cc90101gks5.html


svn checkout svn://svn.code.sf.net/p/qwt/code/branches/qwt-6.1 


designerĿ¼�����QWT�����Դ��
docĿ¼����Ű����ĵ�
examplesĿ¼�����QWT��ʾ����Դ�롢��ִ�г���
srcĿ¼�����QWT��Դ��
textenginesĿ¼�������ѧָ�����Ե��ı������������
������һЩpro�ȹ����ļ��ȡ�



4.��ʼ����
    cd E:\QWT
    qmake qwt.pro  
    nmake  
    ----------�����ĵȴ�-----------  
  
    cd designer  
    qmake designer.pro  
    nmake  
    ----------�����ĵȴ�-----------  
    cd ..  
    cd examples  
    qmake examples.pro  
    nmake 
    ----------�����ĵȴ�-----------  


Ҳ����ʹ��VS2010ֱ�Ӵ�pro���б����Ϊ�򵥡�

5.����
��1����E:\QWT\lib�µ�qwtd.dll��qwt.dll������D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\bin�£�
   ��qwtd.lib��qwt.lib����D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\lib�£���qt��װĿ¼D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010Ϊ������
��2����E:\QWT\designer\plugins\designerĿ¼�µ�qwt_designer_plugin.dll��qwt_designer_plugin.lib������D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\plugins\designerĿ¼�¡�
��3����E:\QWT\srcĿ¼�µ�����.h��.cpp����һ�����ļ���QWT�У��ٽ����ļ��п�����D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\includeĿ¼�¡�

6.ʹ��
    �½���Ŀ��Ȼ��������ã�
��1������->��������->C/C++->���棬���Ӱ���Ŀ¼��$(QTDIR)\include\QWT
��2������->��������->������->���룬���������qwtd.lib
��3������->��������->C/C++->Ԥ��������Ԥ���������壺QWT_DLL

���й���׼�����֮��дһ��demo������һ�£�