#pragma once

#include <QString>

enum ItemType
{
    None,
    Apple
};

class ItemAbstract
{
protected:
    ItemType type = ItemType::None;
    QString picturePath;
    QString soundPath;

public:
    ItemAbstract(ItemType type, QString picturePath, QString soundPath) :
        type(type), picturePath(picturePath), soundPath(soundPath)
    {
    }

    const QString &getPicturePath() const { return this->picturePath; }
    const QString &getSoundPath() const { return this->soundPath; }
};
