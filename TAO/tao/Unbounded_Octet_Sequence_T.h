#ifndef guard_unbounded_octet_sequence_hpp
#define guard_unbounded_octet_sequence_hpp
/**
 * @file
 *
 * @brief Implement octet sequences
 *
 * @author Johnny Willemsen
 */
#include "tao/orbconf.h"

#include "tao/Unbounded_Value_Sequence_T.h"
#include "ace/OS_NS_string.h"

#if (TAO_NO_COPY_OCTET_SEQUENCES == 1)

#include /**/ "tao/TAO_Export.h"
#include "tao/Unbounded_Value_Allocation_Traits_T.h"
#include "tao/Value_Traits_T.h"
#include "tao/Range_Checking_T.h"

#include "tao/Basic_Types.h"
#include "ace/Message_Block.h"
#include "ace/OS_Memory.h"

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

namespace TAO
{
template<>
class TAO_Export unbounded_value_sequence<CORBA::Octet>
{
public:
  typedef CORBA::Octet value_type;
  typedef CORBA::Octet element_type;
  typedef CORBA::Octet const const_value_type;
  typedef value_type & subscript_type;
  typedef value_type const & const_subscript_type;
  typedef ::CORBA::ULong size_type;

  typedef details::unbounded_value_allocation_traits<value_type,true> allocation_traits;
  typedef details::value_traits<value_type,true> element_traits;
  typedef details::generic_sequence<value_type, allocation_traits, element_traits> implementation_type;
  typedef details::range_checking<value_type,true> range;

  inline unbounded_value_sequence()
    : maximum_ (allocation_traits::default_maximum())
    , length_ (0)
    , buffer_ (allocation_traits::default_buffer_allocation())
    , release_ (buffer_ != 0)
    , mb_ (0)
  {}
  inline explicit unbounded_value_sequence(CORBA::ULong maximum)
    : maximum_(maximum)
    , length_(0)
    , buffer_(allocbuf(maximum_))
    , release_(true)
    , mb_ (0)
  {}
  inline unbounded_value_sequence(
      CORBA::ULong maximum,
      CORBA::ULong length,
      value_type * data,
      CORBA::Boolean release = false)
    : maximum_ (maximum),
      length_ (length),
      buffer_ (data),
      release_ (release),
      mb_ (0)
  {}
  inline ~unbounded_value_sequence() {
    if (mb_)
      ACE_Message_Block::release (mb_);
    if (release_)
      freebuf(buffer_);
  }
  /// Create a sequence of octets from a single message block (i.e. it
  /// ignores any chaining in the message block).
  inline unbounded_value_sequence (CORBA::ULong length,
                                                 const ACE_Message_Block* mb)
    : maximum_ (length)
    , length_ (length)
    , buffer_ (reinterpret_cast <CORBA::Octet *>(mb->rd_ptr ()))
    , release_ (false)
    , mb_(0) {
    // Get the message block flags.
    ACE_Message_Block::Message_Flags const flg = mb->self_flags ();

    // If the DONT_DELETE flag is disabled just a duplicate would
    // help. If the DONT_DELETE flag is enabled a deep copy is needed as
    // the contents would be on stack. Just incrementing the ref count
    // on the stack based data block would only crash the program when
    // the stack unwinds
    if (ACE_BIT_DISABLED (flg,
                          ACE_Message_Block::DONT_DELETE))
      {
        this->mb_ = ACE_Message_Block::duplicate (mb);
      }
    else
      {
        // As we are in CORBA mode, all the data blocks would be aligned
        // on an 8 byte boundary
        ACE_Message_Block msgb (*mb, ACE_CDR::MAX_ALIGNMENT);

        // Get the base pointer of the incoming message block
        char *const start = ACE_ptr_align_binary (mb->base (),
                                                  ACE_CDR::MAX_ALIGNMENT);

        // Get the read and write displacements in the incoming stream
        size_t const rd_pos = static_cast<size_t> (mb->rd_ptr () - start);
        size_t const wr_pos = static_cast<size_t> (mb->wr_ptr () - start);

        this->mb_ = ACE_Message_Block::duplicate (&msgb);

        this->mb_->rd_ptr (rd_pos);
        this->mb_->wr_ptr (wr_pos);
      }
  }
  inline CORBA::ULong maximum() const {
    return maximum_;
  }
  inline CORBA::Boolean release() const {
    return release_;
  }
  inline CORBA::ULong length() const {
    return length_;
  }
  inline void length(CORBA::ULong length) {
    if (length <= maximum_)
      {
        if (this->mb_ == 0)
          {
            length_ = length;
          }
        else
          {
            unbounded_value_sequence tmp(length);
            tmp.length_ = length;
            element_traits::copy_range(
              buffer_,
              buffer_ + length,
              tmp.buffer_);
            swap(tmp);
          }
        return;
      }

    unbounded_value_sequence tmp(length);
    tmp.length_ = length;
    element_traits::copy_range(
      buffer_,
      buffer_ + length_,
      tmp.buffer_);
    swap(tmp);
  }
  inline value_type const & operator[](CORBA::ULong i) const {
    range::check(i, length_, maximum_, "operator[]() const");
    return buffer_[i];
  }
  inline value_type & operator[](CORBA::ULong i) {
    range::check(i, length_, maximum_, "operator[]() non-const");
    return buffer_[i];
  }
  inline void replace(
      CORBA::ULong maximum,
      CORBA::ULong length,
      value_type * data,
      CORBA::Boolean release = false) {
    unbounded_value_sequence tmp(maximum, length, data, release);
    swap(tmp);
  }
  inline value_type const * get_buffer() const {
    if (buffer_ == 0)
      {
        buffer_ = allocbuf(maximum_);
        release_ = true;
      }
    return buffer_;
  }
  inline value_type * get_buffer(CORBA::Boolean orphan = false) {
    if (orphan && !release_)
    {
      return 0;
    }
    if (buffer_ == 0)
    {
      buffer_ = allocbuf(maximum_);
      if (!orphan)
        {
          release_ = true;
        }
    }
    if (!orphan)
    {
      return buffer_;
    }

    unbounded_value_sequence tmp;
    swap(tmp);
    tmp.release_ = false;

    return tmp.buffer_;
  }

  // moved inside the class to resolve namespace lookup issues.
  // This is a replacement for the commented block below.
  inline bool operator== (const unbounded_value_sequence & rhs) const {
    unbounded_value_sequence const & lhs = *this;
    CORBA::ULong const len = lhs.length();

    // We use the subscript operator instead of get_buffer() to avoid a
    // potential buffer allocation.
    return
      (len == rhs.length()
       && (len == 0
           ? true
           : ACE_OS::memcmp(&lhs[0], &rhs[0], len) == 0));
  }

  inline bool operator!= (const unbounded_value_sequence & rhs) const
  {
    return !this->operator==(rhs);
  }

  inline void swap(unbounded_value_sequence & rhs) noexcept {
    std::swap (mb_, rhs.mb_);
    std::swap (maximum_, rhs.maximum_);
    std::swap (length_, rhs.length_);
    std::swap (buffer_, rhs.buffer_);
    std::swap (release_, rhs.release_);
  }
  static value_type * allocbuf(CORBA::ULong maximum) {
    return allocation_traits::allocbuf(maximum);
  }
  static void freebuf(value_type * buffer) {
    allocation_traits::freebuf(buffer);
  }

  /// Returns the underlying message block, the caller must *not*
  /// release the copy.
  inline ACE_Message_Block* mb () const {
    return mb_;
  }

  /// Replaces the current buffer with @a mb, using only @a length bytes.
  /// It takes a duplicate of <mb> so the user still owns it.
  inline void replace (CORBA::ULong length, const ACE_Message_Block* mb) {
    unbounded_value_sequence s (length, mb);
    swap (s);
  }

  unbounded_value_sequence (
    const unbounded_value_sequence &rhs)
    : maximum_ (0)
    , length_ (0)
    , buffer_(0)
    , release_(false)
    , mb_ (0)
  {
    if (rhs.maximum_ == 0 || rhs.buffer_ == 0)
    {
      maximum_ = rhs.maximum_;
      length_ = rhs.length_;
      return;
    }
    unbounded_value_sequence tmp(rhs.maximum_);
    tmp.length_ = rhs.length_;
    if (rhs.mb_ == 0)
      {
        ACE_OS::memcpy (tmp.buffer_,
                        rhs.buffer_,
                        rhs.length_);
      }
    else
      {
        size_t offset = 0;
        for (const ACE_Message_Block *i = rhs.mb_; i != 0; i = i->cont ())
          {
            ACE_OS::memcpy (tmp.buffer_ + offset,
                            i->rd_ptr (),
                            i->length ());

            offset += i->length ();
          }
      }
    swap(tmp);
  }

  unbounded_value_sequence &
  operator= (const unbounded_value_sequence & rhs)
  {
    unbounded_value_sequence tmp(rhs);
    swap(tmp);
    return * this;
  }

private:
  /// The maximum number of elements the buffer can contain.
  CORBA::ULong maximum_;

  /// The current number of elements in the buffer.
  CORBA::ULong length_;

  /// The buffer with all the elements, casting must be done in derived
  /// classes.
  mutable value_type * buffer_;

  /// If true then the sequence should release the buffer when it is
  /// destroyed.
  mutable CORBA::Boolean release_;
  ACE_Message_Block* mb_;
};
} // namespace TAO

TAO_END_VERSIONED_NAMESPACE_DECL

#endif /* TAO_NO_COPY_OCTET_SEQUENCES == 1 */

#if (TAO_NO_COPY_OCTET_SEQUENCES == 0)

// This doesn't work always for unexplained reason. At least
// PortableServer::Active_Object_Map.cpp fails to compile with some compilers.
// But I'm keeping this in for the moment so that it may be
// resurrected if need be
inline
bool
operator== (const TAO_VERSIONED_NAMESPACE_NAME::TAO::unbounded_value_sequence<CORBA::Octet> & lhs,
            const TAO_VERSIONED_NAMESPACE_NAME::TAO::unbounded_value_sequence<CORBA::Octet> & rhs)
{
  ::CORBA::ULong const rlen = rhs.length ();

  if (rlen != lhs.length ())
    {
      return false;
    }

  const CORBA::Octet * rhs_buff = rhs.get_buffer ();
  const CORBA::Octet * lhs_buff = lhs.get_buffer ();
  const bool result = (ACE_OS::memcmp (lhs_buff, rhs_buff, rlen) == 0);

  return result;
}

inline
bool
operator!= (const TAO_VERSIONED_NAMESPACE_NAME::TAO::unbounded_value_sequence<CORBA::Octet> & lhs,
            const TAO_VERSIONED_NAMESPACE_NAME::TAO::unbounded_value_sequence<CORBA::Octet> & rhs)
{
  return !(lhs == rhs);
}
#endif /* TAO_NO_COPY_OCTET_SEQUENCES==0 */

#endif // guard_unbounded_octet_sequence_hpp
