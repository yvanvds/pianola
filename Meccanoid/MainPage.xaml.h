//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "ConnectorClass.h"

namespace Meccanoid
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
    void NotifyUser(Platform::String^ message);

  private:
    ConnectorClass^ connector;

  internal:
    static MainPage^ Current;
	};
}
