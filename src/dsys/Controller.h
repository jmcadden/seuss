// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#ifndef DSYS_CONTROLLER_H_
#define DSYS_CONTROLLER_H_
#ifdef __ebbrt__
#include <ebbrt/native/Net.h>
#else
#include <boost/asio.hpp>
#endif

#include <ebbrt/EbbId.h>
#include <ebbrt/GlobalStaticIds.h>
#include <ebbrt/SharedEbb.h>

#include "MemberSet.h"

namespace ebbrt {
namespace dsys {
  using MemberId = std::string;

/** dsys::Controller 
  * The dsys controller is local handle to the distributed system at large
  *
  */
class Controller : public ebbrt::SharedEbb<Controller>,
                   public ebbrt::MemberSet<Controller> {

public:
  static const ebbrt::EbbId global_id =
      ebbrt::GenerateStaticEbbId("DsysController");
  Controller(ebbrt::EbbId id) : MemberSet<Controller>(id){};
  void MemberSetEventMemberAdd(MemberId id) override;
  void MemberSetEventMemberDelete(MemberId id) override;
  
  void AllocateNativeInstances(std::string binary_path);
private:
  std::vector<ebbrt::NodeAllocator::NodeDescriptor> node_descriptors_;
};

constexpr auto controller =
    ebbrt::EbbRef<Controller>(Controller::global_id);

} // namespace dsys
} // namespace ebbrt
#endif //DSYS_CONTROLLER_H_
