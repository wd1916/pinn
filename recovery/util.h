#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QByteArray>
#include <QVariant>
#include <sys/syscall.h>
#include <linux/reboot.h>

/*
 * Convenience functions
 *
 * Initial author: Floris Bos
 * Maintained by Raspberry Pi
 *
 * See LICENSE.txt for license details
 */

typedef enum eNAMEPARTS_T
{   // Name = eBASE - eFLAVOUR#eDATE@ePART
    eBASE=1,
    eFLAVOUR=2,
    eDATE=4,
    ePART=8,
    eSPLIT=16,  //Do not return prefix

    //Useful combinations
    eCORE=eBASE|eFLAVOUR,           //Normally used name
    eBACKUP=eBASE|eFLAVOUR|eDATE,   //Normal name + backup date
    eUNIQUE=eBASE|eFLAVOUR|ePART,   //Name name + partition info
    eFULL=eBASE|eFLAVOUR|eDATE|ePART//Everything
} eNAMEPARTS;

QByteArray getFileContents(const QString &filename);
void putFileContents(const QString &filename, const QByteArray &data);
QByteArray getRemoteFile(const QString &url);
void getOverscan(int &top, int &bottom, int &left, int &right);
bool nameMatchesRiscOS(const QString &name);
uint readBoardRevision();
bool canBootOs(const QString& name, const QVariantMap& values);
bool setRebootPartition(QByteArray partition);
void reboot();
QByteArray partdev(const QString &drivedev, int nr);
QByteArray sysclassblock(const QString &drivedev, int partnr = -1);
bool isURL(const QString &s);

QByteArray getLabel(const QString part);
QByteArray getUUID(const QString part);
QByteArray getDiskId(const QString &device);
QByteArray getPartUUID(const QString &devpart);
QByteArray getDevice(const QString & partuuid);

QString getNameParts(const QString& input, eNAMEPARTS flags);
int extractPartitionNumber(QByteArray& partition);

#endif // UTIL_H
