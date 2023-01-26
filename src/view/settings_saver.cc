#include "settings_saver.h"

namespace view {

SettingsSaver::SettingsSaver(const QString& file, QObject* parent)
    : QSettings(file, QSettings::NativeFormat, parent) {}

void SettingsSaver::SaveProjectionType(bool projection_type) {
  beginGroup("Projection settings");
  setValue("type", projection_type);
  endGroup();
}

void SettingsSaver::SaveBackgroundColor(const QColor& color) {
  beginGroup("Background settings");
  SaveColor(color);
  endGroup();
}

void SettingsSaver::SavePointStyle(const SceneObjectSettings& settings) {
  SaveSceneObjectStyle("Points settings", settings);
}

void SettingsSaver::SaveLineStyle(const SceneObjectSettings& settings) {
  SaveSceneObjectStyle("Lines settings", settings);
}

bool SettingsSaver::GetProjectionType() {
  beginGroup("Projection settings");
  bool result = value("type", true).toBool();
  endGroup();
  return result;
}

QColor SettingsSaver::GetBackgroundColor() {
  beginGroup("Background settings");
  QColor result = GetColor("Background settings", "white");
  endGroup();
  return result;
}

SceneObjectSettings SettingsSaver::GetPointStyle() {
  return GetSceneObjectSettings("Points settings", "red");
}

SceneObjectSettings SettingsSaver::GetLineStyle() {
  return GetSceneObjectSettings("Lines settings", "pink");
}

void SettingsSaver::SaveSceneObjectStyle(const QString& group,
                                         const SceneObjectSettings& settings) {
  beginGroup(group);
  setValue("type", settings.type);
  setValue("size", settings.size);
  SaveColor(settings.color);
  endGroup();
}

SceneObjectSettings SettingsSaver::GetSceneObjectSettings(
    const QString& group, const QColor& default_color) {
  SceneObjectSettings result;
  beginGroup(group);
  result.type = value("type", 1).toInt();
  result.size = value("size", 1.0F).toFloat();
  result.color = GetColor(group, default_color);
  endGroup();
  return result;
}

void SettingsSaver::SaveColor(const QColor& color) {
  setValue("red", color.redF());
  setValue("green", color.greenF());
  setValue("blue", color.blueF());
}

QColor SettingsSaver::GetColor(const QString& group,
                               const QColor& default_color) {
  QColor result;
  result.setRedF(value("red", default_color.redF()).toFloat());
  result.setGreenF(value("green", default_color.greenF()).toFloat());
  result.setBlueF(value("blue", default_color.blueF()).toFloat());
  return result;
}

}  // namespace view
