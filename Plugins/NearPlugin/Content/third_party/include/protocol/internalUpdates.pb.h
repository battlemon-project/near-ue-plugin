// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: internalUpdates.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_internalUpdates_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_internalUpdates_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021005 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_internalUpdates_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_internalUpdates_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_internalUpdates_2eproto;
namespace game {
namespace battlemon {
namespace updates {
class InternalUpdate;
struct InternalUpdateDefaultTypeInternal;
extern InternalUpdateDefaultTypeInternal _InternalUpdate_default_instance_;
}  // namespace updates
}  // namespace battlemon
}  // namespace game
PROTOBUF_NAMESPACE_OPEN
template<> ::game::battlemon::updates::InternalUpdate* Arena::CreateMaybeMessage<::game::battlemon::updates::InternalUpdate>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace game {
namespace battlemon {
namespace updates {

// ===================================================================

class InternalUpdate final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:game.battlemon.updates.InternalUpdate) */ {
 public:
  inline InternalUpdate() : InternalUpdate(nullptr) {}
  ~InternalUpdate() override;
  explicit PROTOBUF_CONSTEXPR InternalUpdate(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  InternalUpdate(const InternalUpdate& from);
  InternalUpdate(InternalUpdate&& from) noexcept
    : InternalUpdate() {
    *this = ::std::move(from);
  }

  inline InternalUpdate& operator=(const InternalUpdate& from) {
    CopyFrom(from);
    return *this;
  }
  inline InternalUpdate& operator=(InternalUpdate&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const InternalUpdate& default_instance() {
    return *internal_default_instance();
  }
  static inline const InternalUpdate* internal_default_instance() {
    return reinterpret_cast<const InternalUpdate*>(
               &_InternalUpdate_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(InternalUpdate& a, InternalUpdate& b) {
    a.Swap(&b);
  }
  inline void Swap(InternalUpdate* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(InternalUpdate* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  InternalUpdate* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<InternalUpdate>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const InternalUpdate& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const InternalUpdate& from) {
    InternalUpdate::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(InternalUpdate* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "game.battlemon.updates.InternalUpdate";
  }
  protected:
  explicit InternalUpdate(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNearIdsFieldNumber = 1,
    kMessageFieldNumber = 2,
    kRemoveOnFailFieldNumber = 3,
  };
  // repeated string near_ids = 1;
  int near_ids_size() const;
  private:
  int _internal_near_ids_size() const;
  public:
  void clear_near_ids();
  const std::string& near_ids(int index) const;
  std::string* mutable_near_ids(int index);
  void set_near_ids(int index, const std::string& value);
  void set_near_ids(int index, std::string&& value);
  void set_near_ids(int index, const char* value);
  void set_near_ids(int index, const char* value, size_t size);
  std::string* add_near_ids();
  void add_near_ids(const std::string& value);
  void add_near_ids(std::string&& value);
  void add_near_ids(const char* value);
  void add_near_ids(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& near_ids() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_near_ids();
  private:
  const std::string& _internal_near_ids(int index) const;
  std::string* _internal_add_near_ids();
  public:

  // string message = 2;
  void clear_message();
  const std::string& message() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_message(ArgT0&& arg0, ArgT... args);
  std::string* mutable_message();
  PROTOBUF_NODISCARD std::string* release_message();
  void set_allocated_message(std::string* message);
  private:
  const std::string& _internal_message() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message(const std::string& value);
  std::string* _internal_mutable_message();
  public:

  // bool remove_on_fail = 3;
  void clear_remove_on_fail();
  bool remove_on_fail() const;
  void set_remove_on_fail(bool value);
  private:
  bool _internal_remove_on_fail() const;
  void _internal_set_remove_on_fail(bool value);
  public:

  // @@protoc_insertion_point(class_scope:game.battlemon.updates.InternalUpdate)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> near_ids_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
    bool remove_on_fail_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_internalUpdates_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// InternalUpdate

// repeated string near_ids = 1;
inline int InternalUpdate::_internal_near_ids_size() const {
  return _impl_.near_ids_.size();
}
inline int InternalUpdate::near_ids_size() const {
  return _internal_near_ids_size();
}
inline void InternalUpdate::clear_near_ids() {
  _impl_.near_ids_.Clear();
}
inline std::string* InternalUpdate::add_near_ids() {
  std::string* _s = _internal_add_near_ids();
  // @@protoc_insertion_point(field_add_mutable:game.battlemon.updates.InternalUpdate.near_ids)
  return _s;
}
inline const std::string& InternalUpdate::_internal_near_ids(int index) const {
  return _impl_.near_ids_.Get(index);
}
inline const std::string& InternalUpdate::near_ids(int index) const {
  // @@protoc_insertion_point(field_get:game.battlemon.updates.InternalUpdate.near_ids)
  return _internal_near_ids(index);
}
inline std::string* InternalUpdate::mutable_near_ids(int index) {
  // @@protoc_insertion_point(field_mutable:game.battlemon.updates.InternalUpdate.near_ids)
  return _impl_.near_ids_.Mutable(index);
}
inline void InternalUpdate::set_near_ids(int index, const std::string& value) {
  _impl_.near_ids_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set:game.battlemon.updates.InternalUpdate.near_ids)
}
inline void InternalUpdate::set_near_ids(int index, std::string&& value) {
  _impl_.near_ids_.Mutable(index)->assign(std::move(value));
  // @@protoc_insertion_point(field_set:game.battlemon.updates.InternalUpdate.near_ids)
}
inline void InternalUpdate::set_near_ids(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _impl_.near_ids_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:game.battlemon.updates.InternalUpdate.near_ids)
}
inline void InternalUpdate::set_near_ids(int index, const char* value, size_t size) {
  _impl_.near_ids_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:game.battlemon.updates.InternalUpdate.near_ids)
}
inline std::string* InternalUpdate::_internal_add_near_ids() {
  return _impl_.near_ids_.Add();
}
inline void InternalUpdate::add_near_ids(const std::string& value) {
  _impl_.near_ids_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:game.battlemon.updates.InternalUpdate.near_ids)
}
inline void InternalUpdate::add_near_ids(std::string&& value) {
  _impl_.near_ids_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:game.battlemon.updates.InternalUpdate.near_ids)
}
inline void InternalUpdate::add_near_ids(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _impl_.near_ids_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:game.battlemon.updates.InternalUpdate.near_ids)
}
inline void InternalUpdate::add_near_ids(const char* value, size_t size) {
  _impl_.near_ids_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:game.battlemon.updates.InternalUpdate.near_ids)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
InternalUpdate::near_ids() const {
  // @@protoc_insertion_point(field_list:game.battlemon.updates.InternalUpdate.near_ids)
  return _impl_.near_ids_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
InternalUpdate::mutable_near_ids() {
  // @@protoc_insertion_point(field_mutable_list:game.battlemon.updates.InternalUpdate.near_ids)
  return &_impl_.near_ids_;
}

// string message = 2;
inline void InternalUpdate::clear_message() {
  _impl_.message_.ClearToEmpty();
}
inline const std::string& InternalUpdate::message() const {
  // @@protoc_insertion_point(field_get:game.battlemon.updates.InternalUpdate.message)
  return _internal_message();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void InternalUpdate::set_message(ArgT0&& arg0, ArgT... args) {
 
 _impl_.message_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:game.battlemon.updates.InternalUpdate.message)
}
inline std::string* InternalUpdate::mutable_message() {
  std::string* _s = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:game.battlemon.updates.InternalUpdate.message)
  return _s;
}
inline const std::string& InternalUpdate::_internal_message() const {
  return _impl_.message_.Get();
}
inline void InternalUpdate::_internal_set_message(const std::string& value) {
  
  _impl_.message_.Set(value, GetArenaForAllocation());
}
inline std::string* InternalUpdate::_internal_mutable_message() {
  
  return _impl_.message_.Mutable(GetArenaForAllocation());
}
inline std::string* InternalUpdate::release_message() {
  // @@protoc_insertion_point(field_release:game.battlemon.updates.InternalUpdate.message)
  return _impl_.message_.Release();
}
inline void InternalUpdate::set_allocated_message(std::string* message) {
  if (message != nullptr) {
    
  } else {
    
  }
  _impl_.message_.SetAllocated(message, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.message_.IsDefault()) {
    _impl_.message_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:game.battlemon.updates.InternalUpdate.message)
}

// bool remove_on_fail = 3;
inline void InternalUpdate::clear_remove_on_fail() {
  _impl_.remove_on_fail_ = false;
}
inline bool InternalUpdate::_internal_remove_on_fail() const {
  return _impl_.remove_on_fail_;
}
inline bool InternalUpdate::remove_on_fail() const {
  // @@protoc_insertion_point(field_get:game.battlemon.updates.InternalUpdate.remove_on_fail)
  return _internal_remove_on_fail();
}
inline void InternalUpdate::_internal_set_remove_on_fail(bool value) {
  
  _impl_.remove_on_fail_ = value;
}
inline void InternalUpdate::set_remove_on_fail(bool value) {
  _internal_set_remove_on_fail(value);
  // @@protoc_insertion_point(field_set:game.battlemon.updates.InternalUpdate.remove_on_fail)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace updates
}  // namespace battlemon
}  // namespace game

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_internalUpdates_2eproto
