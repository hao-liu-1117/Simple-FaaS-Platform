#ifndef PREFIX_H_
#define PREFIX_H_

#include <string>
// Prefix of caw data. Prefix should be added in methods instaead of request.
namespace prefix {
  const std::string kUser = std::string("user_"); // username with prefix - username (check if username exists)
  const std::string kFollowing = std::string("following_"); // (following_ + username) - set of following
  const std::string kFollowers = std::string("followers_"); // (followers_ + username) - set of followers

  const std::string kCawId = std::string("caw_id_"); // caw_id with prefix - caw_id (check if caw_id exists)
  // kCawCount is not a prefix but a individual key.
  const std::string kCawCount = std::string("caw_count"); // kCawCount - number of current caws.
  const std::string kCawInitId = std::string("0"); // first caw_id = 0
  const std::string kCawUser = std::string("cawuser_"); // (cawuser_ + caw_id) -- username
  const std::string kCawText = std::string("cawtext_"); // (cawtext_ + caw_id) -- text
  const std::string kCawParentId = std::string("caw_parent_id_"); // (caw_parent_id_ + caw_id) -- caw_id
  const std::string kCawSonId = std::string("caw_son_id_"); // (caw_son_id + caw_id) -- caw_id
  const std::string kCawSeconds = std::string("cawseconds_"); // (cawseconds_ + caw_id) -- timestamp seconds
  const std::string kCawUSeconds = std::string("cawuseconds_"); // (cawuseconds_ + caw_id) -- timestamp useconds

  const std::string kEventType = std::string("event_"); // (event_ + event_id) -- functions
  // prefix for Stream 
  const std::string kStream_tag2caws = std::string("stream_tag2caws_"); // (stream_tag2caws_hashtag) -- set of serilized caws that contains hashtag
} // namespace prefix

#endif
