//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Meccanoid;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage^ MainPage::Current = nullptr;

MainPage::MainPage()
{
	InitializeComponent();
  MainPage::Current = this;

  lPos    = ref new Array<TextBlock^>{ lPos0, lPos1, lPos2, lPos3, lPos4, lPos5, lPos6, lPos7, lPos8, lPos9, lPos10, lPos11, lPos12, lPos13, lPos14, lPos15 };
  lSpeed  = ref new Array<TextBlock^>{ lSpeed0, lSpeed1, lSpeed2, lSpeed3, lSpeed4, lSpeed5, lSpeed6, lSpeed7, lSpeed8, lSpeed9, lSpeed10, lSpeed11, lSpeed12, lSpeed13, lSpeed14, lSpeed15 };
  lTarget = ref new Array<TextBlock^>{ lTarget0, lTarget1, lTarget2, lTarget3, lTarget4, lTarget5, lTarget6, lTarget7, lTarget8, lTarget9, lTarget10, lTarget11, lTarget12, lTarget13, lTarget14, lTarget15 };

  connector = ref new ConnectorClass();
}

void Meccanoid::MainPage::SetName(String ^ name)
{
  lName->Text = name;
}

void Meccanoid::MainPage::SetConnected(bool value)
{
  if (value) {
    lConnected->Text = "Yes";
  }
  else {
    lConnected->Text = "No";
  }
}

void Meccanoid::MainPage::SetCycle(int ms)
{
  lCycle->Text = "" + ms;
}

void Meccanoid::MainPage::SetIP(String ^ ip, String ^ port)
{
  lIP->Text = ip;
  lPort->Text = port;
  SetConnected(true);
}

void Meccanoid::MainPage::SetServoPos(int ID, float value)
{
  lPos[ID]->Text = "" + value;
}

void Meccanoid::MainPage::SetServoTarget(int ID, int target, float speed)
{
  lTarget[ID]->Text = "" + target;
  lSpeed [ID]->Text = "" + speed ;
}



void Meccanoid::MainPage::textBlock_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
