/*
 * This file is part of buteo-syncfw package
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Sateesh Kavuri <sateesh.kavuri@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */


#ifndef SYNCPROFILE_H
#define SYNCPROFILE_H

#include "Profile.h"
#include "SyncLog.h"
#include "SyncSchedule.h"


namespace Buteo {

class SyncProfilePrivate;
    
/*! \brief A top level synchronization profile.
 *
 * SyncProfile is derived from Profile. It represents a top level
 * synchronization profile, which contains all settings needed for a
 * synchronization session. A SyncProfile typically has sub-profiles for the
 * used service, client/server plug-in and storage plug-ins. SyncProfile
 * extends the Profile inteface with functions for accessing information about
 * synchronization schedule and history of finished synchronization sessions
 * with this profile.
 */
class SyncProfile : public Profile
{
public:
    //! Synchronization types.
    enum SyncType
    {
        //! Synchronization is started manually.
        SYNC_MANUAL,

        //! Synchronization is triggered automatically based on a defined
        //! schedule.
        SYNC_SCHEDULED
    };

    //! Sync destination type.
    enum DestinationType
    {
        //! Destination is a device (N95, Harmattan, OviSuite etc.)
        DESTINATION_TYPE_DEVICE,

        //! Destination is an online service.
        DESTINATION_TYPE_ONLINE,

        //! Destination type is not defined.
        DESTINATION_TYPE_UNDEFINED
    };

    //! Sync direction for device-to-device syncs.
    enum SyncDirection
    {
        //! Two way sync.
        SYNC_DIRECTION_TWO_WAY,

        //! Data is copied from remote device only.
        SYNC_DIRECTION_FROM_REMOTE,

        //! Data is copied to remote device only.
        SYNC_DIRECTION_TO_REMOTE,

        //! Sync direction is not defined.
        SYNC_DIRECTION_UNDEFINED
    };

    //! Conflict resolution policy for device-to-device syncs.
    enum ConflictResolutionPolicy
    {
        //! Prefer client data in conflict situation.
        CR_POLICY_PREFER_CLIENT,

        //! Prefer server data in conflict situation.
        CR_POLICY_PREFER_SERVER,

        //! Conflict resolution policy is undefined.
        CR_POLICY_UNDEFINED
    };

    /*! \brief Constructs an empty SyncProfile with the given name.
     *
     * \param aName Name of the profile to create.
     */
    explicit SyncProfile(const QString &aName);

    /*! \brief Constructs a SyncProfile from the given XML.
     *
     * \param aRoot Root element of the XML node tree.
     */
    explicit SyncProfile(const QDomElement &aRoot);

    /*! \brief Copy constructor.
     *
     * \param aSource Copy source.
     */
    SyncProfile(const SyncProfile &aSource);

    //! \brief Destructor.
    ~SyncProfile();

    /*! \brief Creates a clone of the sync profile.
     *
     * \return The clone.
     */
    virtual SyncProfile *clone() const;

    
    /*! \brief Sets the name for the profile and associated log.
     */
    virtual void setName(const QString &aName);
    
    
    //! \see Profile::toXml
    virtual QDomElement toXml(QDomDocument &aDoc, bool aLocalOnly = true) const;

    /*! \brief Gets the time of last completed sync session with this profile.
     *
     * \return Last sync time. Null object if this could not be determined.
     */
    QDateTime lastSyncTime() const;

    /*! \brief Gets the next scheduled sync time.
     *
     * \return Next sync time. Null object if the sync type is manual or the
     *  time could not be determined for some other reason.
     */
    virtual QDateTime nextSyncTime() const;

    /*! \brief Gets the results of the last sync from the sync log.
     *
     * \return The results. NULL if not available.
     */
    const SyncResults *lastResults() const;

    /*! \brief Gets the synchronization log associated with this profile.
     *
     * \return The sync log. NULL if no log is set.
     */
    const SyncLog *log() const;

    /*! \brief Sets the synchronization log for this profile.
     *
     * The ownership of the given log object is transferred to this object.
     * If a log is already set, the old log object is deleted first.
     * \param aLog The log.
     */
    void setLog(SyncLog *aLog);

    /*! \brief Adds synchronization results to the log.
     *
     * If a log does not exist yet, an empty log is created first.
     * \param aResults Results to add.
     */
    void addResults(const SyncResults &aResults);

    /*! \brief Gets the sync type of this profile.
     *
     * \return The sync type.
     */
    SyncType syncType() const;

    /*! \brief Sets the sync type of this profile (manual/scheduled).
     *
     * \param aType The new sync type.
     */
    void setSyncType(SyncType aType);

    /*! \brief Gets the names of storage backends used by this profile.
     *
     * \return List of storage backend names.
     */
    QStringList storageBackendNames() const;

    /*! \brief Gets sync schedule settings.
     *
     * \return Sync schedule.
     */
    SyncSchedule syncSchedule() const;

    /*! \brief Sets sync schedule settings.
     *
     * \param aSchedule New schedule.
     */
    void setSyncSchedule(const SyncSchedule &aSchedule);

    /*! \brief Get the first service sub-profile.
     *
     * \return Service profile. NULL if not found.
     */
    const Profile *serviceProfile() const;

    /*! \brief Get the first service sub-profile.
     *
     * \return Service profile. NULL if not found.
     */
    Profile *serviceProfile();

    /*! \brief Get the first client sub-profile.
     *
     * \return Client profile. NULL if not found.
     */
    const Profile *clientProfile() const;

    /*! \brief Get the first client sub-profile.
     *
     * \return Client profile. NULL if not found.
     */
    Profile *clientProfile();

    /*! \brief Get the first server sub-profile.
     *
     * \return Server profile. NULL if not found.
     */
    const Profile *serverProfile() const;

    /*! \brief Get the first server sub-profile.
     *
     * \return Server profile. NULL if not found.
     */
    Profile *serverProfile();

    /*! \brief Get the storage sub-profiles.
     *
     * \return Storage profiles.
     */
    QList<const Profile*> storageProfiles() const;

    /*! \brief Get the storage sub-profiles.
     *
     * \return Storage profiles.
     */
    QList<Profile*> storageProfilesNonConst();

    /*! \brief Gets sync destination type (device or online).
     *
     * \return Destination type.
     */
    DestinationType destinationType() const;

    /*! \brief Gets sync direction (two way, to destination, from destination).
     *
     * \return Sync direction.
     */
    SyncDirection syncDirection() const;

     /*! \brief Sets sync direction.
     *
     * \return New sync direction.
     */
    void setSyncDirection(SyncDirection aDirection);

    /*! \brief Gets conflict resolution policy.
     *
     * \return Conflict resolution policy.
     */
    ConflictResolutionPolicy conflictResolutionPolicy() const;

    /*! \brief Set conflict resolution policy.
     *
     * \return Conflict resolution policy.
     */
    void setConflictResolutionPolicy(ConflictResolutionPolicy aPolicy);

    /*! \brief Get the service name of profile.
     *
     * \return Service name associated with profile.
     */
    QString serviceName() const;

private:

    SyncProfile& operator=(const SyncProfile &aRhs);

    SyncProfilePrivate *d_ptr;
};

}

#endif // SYNCPROFILE_H
