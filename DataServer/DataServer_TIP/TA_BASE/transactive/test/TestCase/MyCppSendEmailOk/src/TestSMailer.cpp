///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use SMailer.
// Written by Morning, mailto:moyingzz@etang.com
//
// Date:2003-5
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
#include "SMailer.h"
#include "WinSockHelper.h"

void main()
{
    MUtils::WinSockHelper wshelper;
	
    // make sure the file 'boot.ini' is in the root directory on driver C
    SMailer::TextPlainContent  content1("plain text content");
    SMailer::TextHtmlContent   content2("<a href='http://morningspace.51.net'>click me</a>");
    SMailer::AppOctStrmContent content3("c:\\smtp_boot.ini");
	
    SMailer::MailInfo info;
    info.setSenderName("linshenglong888");
    info.setSenderAddress("linshenglong888@126.com");
    info.addReceiver("linshenglong777", "linshenglong777@126.com");
    info.addReceiver("shenglonglin1986", "shenglonglin1986@gmail.com");
    info.setPriority(SMailer::Priority::normal);
    info.setSubject("a test mail");
    info.addMimeContent(&content1);
    info.addMimeContent(&content2);
    info.addMimeContent(&content3);
	
    try
    {
        SMailer::MailSender sender("smtp.126.com", "linshenglong888", "051335");
        sender.setMail(&SMailer::MailWrapper(&info));
        sender.sendMail();
    }
    catch (SMailer::MailException& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unkown error" << std::endl;
    }
}