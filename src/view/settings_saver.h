#ifndef SETTINGSSAVER_H
#define SETTINGSSAVER_H

#include <QColor>
#include <QObject>
#include <QSettings>

namespace view {

struct SceneObjectSettings {
  int type;
  float size;
  QColor color;
};

class SettingsSaver : protected QSettings {
  Q_OBJECT

 public:
  explicit SettingsSaver(const QString& file, QObject* parent = nullptr);

  void SaveProjectionType(bool projection_type);
  void SaveBackgroundColor(const QColor& color);
  void SavePointStyle(const SceneObjectSettings& settings);
  void SaveLineStyle(const SceneObjectSettings& settings);

  bool GetProjectionType();
  QColor GetBackgroundColor();
  SceneObjectSettings GetPointStyle();
  SceneObjectSettings GetLineStyle();

 private:
  void SaveSceneObjectStyle(const QString& group,
                            const SceneObjectSettings& settings);

  SceneObjectSettings GetSceneObjectSettings(const QString& group,
                                             const QColor& default_color);
  void SaveColor(const QColor& color);
  QColor GetColor(const QString& group, const QColor& default_color);
};

}  // namespace view

#endif  // SETTINGSSAVER_H
