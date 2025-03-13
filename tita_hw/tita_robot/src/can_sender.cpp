#include "tita_robot/can_sender.hpp"

namespace can_device
{
bool MotorsCanSendApi::send_command_can_channel_input(api_channel_input_t data)
{
  data.timestamp = get_current_time();
  struct canfd_frame frame;
  frame.can_id = CAN_ID_CHANNEL_INPUT;
  frame.len = 40u;
  memset(frame.data, 0x00U, sizeof(frame.data));
  
  std::memcpy(frame.data, &data, sizeof(data));

  return can_send_api_->send_can_message(frame);
}

bool MotorsCanSendApi::send_command_can_rpc_request(api_rpc_response_t data){
  data.timestamp = get_current_time();

  struct canfd_frame frame;
  frame.can_id = CAN_ID_RPC_REQUEST;
  frame.len = 10U;

  memset(frame.data, 0x00U, sizeof(frame.data));

  std::memcpy(frame.data, &data.timestamp, sizeof(data.timestamp));
  std::memcpy(frame.data + 4, &data.key, sizeof(data.key));
  std::memcpy(frame.data + 6, &data.value, sizeof(data.value));

  return can_send_api_->send_can_message(frame);
}

bool MotorsCanSendApi::send_motors_can(std::vector<api_motor_out_t> motors)
{
  if (motors.size() != leg_dof_ * leg_num_) {
    std::cerr << "[MOTORS_CAN_SEND] motors size not equal to robot dof" << std::endl;
    return false;
  }
  if(leg_dof_ == 3){
    api_motor_out_t motor = {};
    auto it = motors.begin() + 3;
    motors.insert(it, motor);
    motors.push_back(motor);
  }
  bool send_success = true;
  struct canfd_frame frame;
  frame.len = 48U;
  auto now = get_current_time();
  for (size_t id(0); id < motors.size()/2; id++) {
    frame.can_id = CAN_ID_SEND_MOTORS + id;
    memset(frame.data, 0x00U, sizeof(frame.data));
    auto motor = motors[2 * id];
    motor.timestamp = now;
    std::memcpy(frame.data, &motor.timestamp, sizeof(motor.timestamp));
    std::memcpy(frame.data + 4, &motor.position, sizeof(motor.position));
    std::memcpy(frame.data + 8, &motor.kp, sizeof(motor.kp));
    std::memcpy(frame.data + 12, &motor.velocity, sizeof(motor.velocity));
    std::memcpy(frame.data + 16, &motor.kd, sizeof(motor.kd));
    std::memcpy(frame.data + 20, &motor.torque, sizeof(motor.torque));

    motor = motors[2 * id + 1];
    motor.timestamp = now;
    std::memcpy(frame.data + 24, &motor.timestamp, sizeof(motor.timestamp));
    std::memcpy(frame.data + 28, &motor.position, sizeof(motor.position));
    std::memcpy(frame.data + 32, &motor.kp, sizeof(motor.kp));
    std::memcpy(frame.data + 36, &motor.velocity, sizeof(motor.velocity));
    std::memcpy(frame.data + 40, &motor.kd, sizeof(motor.kd));
    std::memcpy(frame.data + 44, &motor.torque, sizeof(motor.torque));
    send_success &= can_send_api_->send_can_message(frame);
    std::this_thread::sleep_for(std::chrono::microseconds(150)); // 等待 100 微秒
  }
  return send_success;
}

}  // namespace can_device