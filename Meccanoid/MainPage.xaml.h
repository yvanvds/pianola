//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "ConnectorClass.h"

using namespace Platform;
using namespace Windows::UI::Xaml::Controls;

namespace Meccanoid
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
    MainPage();
    
    void SetName     (String^ name );
    void SetConnected(bool    value);
    void SetCycle    (int     ms   );

    void SetIP(String^ ip, String^ port);

    void SetServoPos   (int ID, float value             );
    void SetServoTarget(int ID, int target , float speed);

  private:
    ConnectorClass^ connector;

  internal:
    static MainPage^ Current;
  private:
    void textBlock_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

    Array<TextBlock^> ^ lPos;
    Array<TextBlock^> ^ lSpeed; 
    Array<TextBlock^> ^ lTarget;
  };
}
