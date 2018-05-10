#ifndef _CLOUDBUS_TYPES_H_
#define _CLOUDBUS_TYPES_H_

#include "basictypes.h"
#include "returncode.h"
#include "../dcps_if.h"
#include <vector>

#define  IN
#define  OUT
#define  INOUT

namespace DDS
{

#define HANDLE_NIL_NATIVE                   0
#define START_DDS_PORT 7000

    typedef Long                            DomainId_t;
    typedef Long                            InstanceHandle_t;


    using                                   std::vector;
    typedef std::vector<InstanceHandle_t>   InstanceHandleSeq;
    typedef std::vector<Octet>              OctetSeq;
 
    struct  BuiltinTopicKey_t
    {
        Long value[3];
    };


    typedef Long QosPolicyId_t;

    struct  Duration_t
    {
        Long sec;
        ULong nanosec;
    };

    struct  Time_t
    {
        Long sec;
        ULong nanosec;
    };

    const InstanceHandle_t  HANDLE_NIL = HANDLE_NIL_NATIVE;
    const Long              LENGTH_UNLIMITED = -1;
    const Long              DURATION_INFINITE_SEC = 0x7fffffff;
    const ULong             DURATION_INFINITE_NSEC = 0x7fffffff;
    const ULong             DURATION_ZERO_SEC = 0;
    const ULong             DURATION_ZERO_NSEC = 0;
    const Long              TIME_INVALID_SEC = -1;
    const ULong             TIME_INVALID_NSEC = 0xffffffff;

    typedef ULong StatusKind;
    typedef ULong StatusMask;   // bit-mask StatusKind



    const StatusKind INCONSISTENT_TOPIC_STATUS = 0x0001 << 0;
    const StatusKind OFFERED_DEADLINE_MISSED_STATUS = 0x0001 << 1;
    const StatusKind REQUESTED_DEADLINE_MISSED_STATUS = 0x0001 << 2;
    const StatusKind OFFERED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 5;
    const StatusKind REQUESTED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 6;
    const StatusKind SAMPLE_LOST_STATUS = 0x0001 << 7;
    const StatusKind SAMPLE_REJECTED_STATUS = 0x0001 << 8;
    const StatusKind DATA_ON_READERS_STATUS = 0x0001 << 9;
    const StatusKind DATA_AVAILABLE_STATUS = 0x0001 << 10;
    const StatusKind LIVELINESS_LOST_STATUS = 0x0001 << 11;
    const StatusKind LIVELINESS_CHANGED_STATUS = 0x0001 << 12;
    const StatusKind PUBLICATION_MATCHED_STATUS = 0x0001 << 13;
    const StatusKind SUBSCRIPTION_MATCHED_STATUS = 0x0001 << 14;

    struct  InconsistentTopicStatus
    {
        Long total_count;
        Long total_count_change;
    };

    struct  SampleLostStatus
    {
        Long total_count;
        Long total_count_change;
    };

    enum SampleRejectedStatusKind
    {
        NOT_REJECTED,
        REJECTED_BY_INSTANCES_LIMIT,
        REJECTED_BY_SAMPLES_LIMIT,
        REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
    };

    struct  SampleRejectedStatus
    {
        Long total_count;
        Long total_count_change;
        SampleRejectedStatusKind last_reason;
        InstanceHandle_t  last_instance_handle;
    };

    struct  LivelinessLostStatus
    {
        Long total_count;
        Long total_count_change;
    };

    struct  LivelinessChangedStatus
    {
        Long alive_count;
        Long not_alive_count;
        Long alive_count_change;
        Long not_alive_count_change;
        InstanceHandle_t last_publication_handle;
    };

    struct  OfferedDeadlineMissedStatus
    {
        Long total_count;
        Long total_count_change;
        InstanceHandle_t last_instance_handle;
    };

    struct  RequestedDeadlineMissedStatus
    {
        Long total_count;
        Long total_count_change;
        InstanceHandle_t last_instance_handle;
    };

    struct  QosPolicyCount
    {
        QosPolicyId_t policy_id;
        Long count;
    };


    typedef vector<char> StringSeq;

    typedef vector<QosPolicyCount> QosPolicyCountSeq;

    struct  OfferedIncompatibleQosStatus
    {
        Long total_count;
        Long total_count_change;
        QosPolicyId_t last_policy_id;
        QosPolicyCountSeq policies;
    };

    struct  RequestedIncompatibleQosStatus
    {
        Long total_count;
        Long total_count_change;
        QosPolicyId_t last_policy_id;
        QosPolicyCountSeq policies;
    };

    struct  PublicationMatchedStatus
    {
        Long total_count;
        Long total_count_change;
        Long current_count;
        Long current_count_change;
        InstanceHandle_t last_subscription_handle;
    };

    struct  SubscriptionMatchedStatus
    {
        Long total_count;
        Long total_count_change;
        Long current_count;
        Long current_count_change;
        InstanceHandle_t last_publication_handle;
    };

    enum DurabilityQosPolicyKind
    {
        VOLATILE_DURABILITY_QOS,
        TRANSIENT_LOCAL_DURABILITY_QOS,
        TRANSIENT_DURABILITY_QOS,
        PERSISTENT_DURABILITY_QOS
    };

    enum PresentationQosPolicyAccessScopeKind
    {
        INSTANCE_PRESENTATION_QOS,
        TOPIC_PRESENTATION_QOS,
        GROUP_PRESENTATION_QOS
    };

    enum OwnershipQosPolicyKind
    {
        SHARED_OWNERSHIP_QOS,
        EXCLUSIVE_OWNERSHIP_QOS
    };

    enum LivelinessQosPolicyKind
    {
        AUTOMATIC_LIVELINESS_QOS,
        MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
        MANUAL_BY_TOPIC_LIVELINESS_QOS
    };

    enum ReliabilityQosPolicyKind
    {
        BEST_EFFORT_RELIABILITY_QOS,
        RELIABLE_RELIABILITY_QOS
    };

    enum DestinationOrderQosPolicyKind
    {
        BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
        BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
    };

    enum HistoryQosPolicyKind
    {
        KEEP_LAST_HISTORY_QOS,
        KEEP_ALL_HISTORY_QOS
    };

    struct  QosPolicy
    {
        std::string     name;
    };

    typedef vector<QosPolicy*> QosSeq;

    struct HistoryQosPolicy
    {
        HistoryQosPolicyKind  kind;
        long depth;
    };

    struct PartitionQosPolicy
    {
        StringSeq name;
    };

    struct LifespanQosPolicy
    {
        Duration_t duration;
    };

    struct  UserDataQosPolicy
    {
        OctetSeq value;
    };

    struct  ReliabilityQosPolicy
    {
        ReliabilityQosPolicyKind kind;
        Duration_t max_blocking_time;
    };

    struct  OwnershipQosPolicy
    {
        OwnershipQosPolicyKind kind;
    };


    struct  TopicDataQosPolicy
    {
        OctetSeq value;
    };

    struct  LivelinessQosPolicy
    {
        LivelinessQosPolicyKind kind;
        Duration_t lease_duration;
    };

    struct  OwnershipStrengthQosPolicy
    {
        long value;
    };

    struct  GroupDataQosPolicy
    {
        OctetSeq value;
    };

    struct  DurabilityQosPolicy
    {
        DurabilityQosPolicyKind kind;
    };

    struct  WriterDataLifecycleQosPolicy
    {
        bool autodispose_unregistered_instances;
    };

    struct  LatencyBudgetQosPolicy
    {
        Duration_t duration;
    };

    struct  ResourceLimitsQosPolicy
    {
        long max_samples;
        long max_instances;
        long max_samples_per_instance;
    };


    struct  DeadlineQosPolicy
    {
        Duration_t period;
    };

    struct  DurabilityServiceQosPolicy
    {
        Duration_t service_cleanup_delay;
        HistoryQosPolicyKind history_kind;
        long history_depth;
        long max_samples;
        long max_instances;
        long max_samples_per_instance;
    };

    struct  PresentationQosPolicy
    {
        PresentationQosPolicyAccessScopeKind access_scope;
        bool coherent_access;
        bool ordered_access;
    };

    struct  TimeBasedFilterQosPolicy
    {
        Duration_t minimum_separation;
    };

    struct  TransportPriorityQosPolicy
    {
        long value;
    };

    struct  EntityFactoryQosPolicy
    {
        bool autoenable_created_entities;
    };

    struct  DestinationOrderQosPolicy
    {
        DestinationOrderQosPolicyKind kind;
    };

    struct  ReaderDataLifecycleQosPolicy
    {
        Duration_t autopurge_nowriter_samples_delay;
        Duration_t autopurge_disposed_samples_delay;
    };


    struct  DomainParticipantFactoryQos
    {
        EntityFactoryQosPolicy entity_factory;
    };

    struct  DomainParticipantQos
    {
        UserDataQosPolicy user_data;
        EntityFactoryQosPolicy entity_factory;
    };
    struct  TopicQos
    {
        TopicDataQosPolicy topic_data;
        DurabilityQosPolicy durability;
        DurabilityServiceQosPolicy durability_service;
        DeadlineQosPolicy deadline;
        LatencyBudgetQosPolicy latency_budget;
        LivelinessQosPolicy liveliness;
        ReliabilityQosPolicy reliability;
        DestinationOrderQosPolicy destination_order;
        HistoryQosPolicy history;
        ResourceLimitsQosPolicy resource_limits;
        TransportPriorityQosPolicy transport_priority;
        LifespanQosPolicy lifespan;
        OwnershipQosPolicy ownership;
    };

    struct  DataWriterQos
    {
        DurabilityQosPolicy durability;
        DurabilityServiceQosPolicy durability_service;
        DeadlineQosPolicy deadline;
        LatencyBudgetQosPolicy latency_budget;
        LivelinessQosPolicy liveliness;
        ReliabilityQosPolicy reliability;
        DestinationOrderQosPolicy destination_order;
        HistoryQosPolicy history;
        ResourceLimitsQosPolicy resource_limits;
        TransportPriorityQosPolicy transport_priority;
        LifespanQosPolicy lifespan;
        UserDataQosPolicy user_data;
        OwnershipQosPolicy ownership;
        OwnershipStrengthQosPolicy ownership_strength;
        WriterDataLifecycleQosPolicy writer_data_lifecycle;
    };

    struct  PublisherQos
    {
        PresentationQosPolicy presentation;
        PartitionQosPolicy partition;
        GroupDataQosPolicy group_data;
        EntityFactoryQosPolicy entity_factory;
    };

    struct  DataReaderQos
    {
        DurabilityQosPolicy durability;
        DeadlineQosPolicy deadline;
        LatencyBudgetQosPolicy latency_budget;
        LivelinessQosPolicy liveliness;
        ReliabilityQosPolicy reliability;
        DestinationOrderQosPolicy destination_order;
        HistoryQosPolicy history;
        ResourceLimitsQosPolicy resource_limits;
        UserDataQosPolicy user_data;
        OwnershipQosPolicy ownership;
        TimeBasedFilterQosPolicy time_based_filter;
        ReaderDataLifecycleQosPolicy reader_data_lifecycle;
    };

    struct  SubscriberQos
    {
        PresentationQosPolicy presentation;
        PartitionQosPolicy partition;
        GroupDataQosPolicy group_data;
        EntityFactoryQosPolicy entity_factory;
    };

    struct ParticipantBuiltinTopicData;
    struct TopicBuiltinTopicData;
    struct PublicationBuiltinTopicData;
    struct SubscriptionBuiltinTopicData;
    struct InconsistentTopicStatus;
    struct AllDataDisposedTopicStatus;
    struct SampleLostStatus;
    struct SampleRejectedStatus;
    struct LivelinessLostStatus;
    struct LivelinessChangedStatus;
    struct OfferedDeadlineMissedStatus;
    struct RequestedDeadlineMissedStatus;
    struct QosPolicyCount;
    struct OfferedIncompatibleQosStatus;
    struct RequestedIncompatibleQosStatus;
    struct PublicationMatchedStatus;
    struct SubscriptionMatchedStatus;

    class Condition;
    typedef Condition* Condition_ptr;
	typedef std::vector<Condition> ConditionSeq;

    class GuardCondition;
    typedef GuardCondition* GuardCondition_ptr;

    class StatusCondition;
    typedef StatusCondition* StatusCondition_ptr;

    class Entity;
    typedef Entity* Entity_ptr;

    class DomainEntity;
    typedef DomainEntity* DomainEntity_ptr;

    class DomainParticipant;
    typedef DomainParticipant* DomainParticipant_ptr;

    class DomainParticipantFactory;
    typedef DomainParticipantFactory* DomainParticipantFactory_ptr;

    class Topic;
    typedef Topic* Topic_ptr;

    class TopicListener;
    typedef TopicListener* TopicListener_ptr;

    class TopicDescription;
    typedef TopicDescription* TopicDescription_ptr;

    class ContentFilteredTopic;
    typedef ContentFilteredTopic *ContentFilteredTopic_ptr;

    class MultiTopic;
    typedef MultiTopic *MultiTopic_ptr;

    class Subscriber;
    typedef Subscriber* Subscriber_ptr;

    class DataReader;
    typedef DataReader* DataReader_ptr;
    typedef std::vector<DataReader_ptr> DataReaderSeq;

    class DataReaderListener;
    typedef DataReaderListener* DataReaderListener_ptr;

    class Publisher;
    typedef Publisher* Publisher_ptr;

    class DataWriter;
    typedef DataWriter* DataWriter_ptr;
    typedef std::vector<DataWriter_ptr> DataWriterSeq;

    class DataWriterListener;
    typedef DataWriterListener* DataWriterListener_ptr;

    class PublisherListener;
    typedef PublisherListener* PublisherListener_ptr;

    class SubscriberListener;
    typedef SubscriberListener* SubscriberListener_ptr;

    class DomainParticipantListener;
    typedef DomainParticipantListener* DomainParticipantListener_ptr;
}
#endif