#pragma once

#include <wx/event.h>

class OGLCanvas;

namespace GLUI
{
	class Widget;
	class Animator;

	class Manager
	{
	public:
		Manager(OGLCanvas* canvas);
		~Manager();

		enum
		{
			DOCK_NONE = 0,
			DOCK_LEFT,
			DOCK_TOP,
			DOCK_RIGHT,
			DOCK_BOTTOM,
			DOCK_FILL
		};

		struct WidgetInfo
		{
			string		id;
			Widget*		widget;
			uint8_t		dock;

			WidgetInfo(Widget* widget, string id, uint8_t dock = DOCK_NONE)
				: widget(widget), id(id), dock(dock) {}
		};

		void	addWidget(Widget* widget, string id, uint8_t dock = DOCK_NONE);
		Widget*	getWidget(string id);

		void	update(int time);
		void	drawWidgets();

		// Events
		void	mouseMove(int x, int y);

		// wx Events
		void	onMouseMove(wxMouseEvent& e);
		void	onMouseDown(wxMouseEvent& e);
		void	onMouseUp(wxMouseEvent& e);
		void	onSize(wxSizeEvent& e);

	private:
		OGLCanvas*			canvas;
		vector<WidgetInfo>	widgets;
		dim2_t				canvas_size;

		void	applyDocking(WidgetInfo& inf);
	};
}