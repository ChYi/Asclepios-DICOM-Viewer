#pragma once

#include <QWidget>
#include <vtkRenderWindow.h>
#include "vtkeventfilter.h"
#include "series.h"


namespace asclepios::gui
{
	class WidgetBase : public QWidget
	{
	Q_OBJECT
	public:
		explicit WidgetBase(QWidget* t_parent);
		~WidgetBase() = default;

		enum class WidgetType
		{
			none,
			widget2d,
			widgetmpr,
			widgetvolume
		};

		//getters
		[[nodiscard]] core::Series* getSeries() const { return m_series; }
		[[nodiscard]] core::Image* getImage() const { return m_image; }
		[[nodiscard]] bool getIsImageLoaded() const { return m_isImageLoaded; }
		[[nodiscard]] WidgetType getWidgetType() const { return m_widgetType; }
		[[nodiscard]] QWidget* getTabWidget() const { return m_tabWidget; }
		[[nodiscard]] int getPatientIndex() const { return m_patientIndex; }
		[[nodiscard]] int getStudyInex() const { return m_studyIndex; }
		[[nodiscard]] int getSeriesIndex() const { return m_seriesIndex; }
		[[nodiscard]] int getImageIndex() const { return m_imageIndex; }

		//setters
		void setSeries(core::Series* t_series) { m_series = t_series; }
		void setImage(core::Image* t_image) { m_image = t_image; }
		void setIsImageLoaded(const bool& t_flag) { m_isImageLoaded = t_flag; }
		void setWidgetType(const WidgetType& t_widgetType) { m_widgetType = t_widgetType; }
		void setIndexes(const int& t_patientIndex, const int& t_studyIndex, const int& t_seriesIndex,
		                const int& t_imageIndex);

	protected:
		QWidget* m_tabWidget = {};
		core::Series* m_series = {};
		core::Image* m_image = {};
		vtkSmartPointer<vtkRenderWindow> m_renderWindow[3] = {};
		std::unique_ptr<vtkEventFilter> m_vtkEvents = {};
		bool m_isImageLoaded = false;
		WidgetType m_widgetType = WidgetType::none;
		int m_patientIndex = {};
		int m_studyIndex = {};
		int m_seriesIndex = {};
		int m_imageIndex = {};

		virtual void initView() = 0;
		virtual void initData() = 0;
		virtual void render() = 0;
		virtual void createActivationConnections() = 0;
		virtual void resetView() = 0;
		virtual void setWindowLevel(const int& t_window, const int& t_level) = 0;
		virtual void setSliderValues(const int& t_min, const int& t_max, const int& t_value) = 0;
		void focusInEvent(QFocusEvent* event) override;
	};
}