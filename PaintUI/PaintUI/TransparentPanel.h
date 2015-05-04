#pragma once
using namespace System::Windows;
using namespace System::Windows::Forms;
namespace PaintUI{
	ref class TransparentPanel :
		public Panel
	{
	public:
		TransparentPanel();
		virtual ~TransparentPanel();
	protected:
		virtual property System::Windows::Forms::CreateParams^ CreateParams{
			System::Windows::Forms::CreateParams^ get() override
			{
				System::Windows::Forms::CreateParams^ cp = Panel::CreateParams;
				cp->ExStyle |= 0x00000020; // WS_EX_TRANSPARENT;
				return cp;
			}
		}

		virtual void OnPaintBackground(
			PaintEventArgs^ e
			) override
		{

		}

	};
}
