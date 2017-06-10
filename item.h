#pragma once

#include <QString>

/*
II.1. Класс "Предмет". Должен описывать предмет инвентаря и содержать в себе поля:
Тип предмета, изображение предмета (путь к изображению в ресурсах).
*/
class ItemDescription
{

public:
    ItemDescription(int type, QString imagePath, QString soundPath) :
        type(type), imagePath(imagePath), soundPath(soundPath)
    {
    }

    const int type;
    const QString imagePath;
    const QString soundPath;
};
