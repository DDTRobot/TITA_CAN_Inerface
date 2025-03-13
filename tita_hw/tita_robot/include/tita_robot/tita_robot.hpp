#include "can_receiver.hpp"
#include "can_sender.hpp"

/// @brief 
class tita_robot
{
public:
    tita_robot(size_t num_motors)
    {
        can_receiver_ = std::make_unique<can_device::MotorsImuCanReceiveApi>(num_motors);
        can_sender_ = std::make_unique<can_device::MotorsCanSendApi>(num_motors);
        motor_num_ = num_motors;
    }



    /// @brief Get the current states update timeout.
    /// @return  bool: if current states not update, return true.
    bool data_time_out() const;



    /// @brief Get the current joint positions in joint space.
    /// @return std::vector<double>: current joint positions in radians.
    std::vector<double> get_joint_q() const;

    /// @brief Get the current joint velocities in joint space.
    /// @return std::vector<double>: current joint velocities in radians per second.
    std::vector<double> get_joint_v() const;


    /// @brief Get the current joint torques in joint space.
    /// @return std::vector<double>: current joint torques in Newton meters.
    std::vector<double> get_joint_t() const;


    /// @brief Get the current joint status.
    /// @note  Joints status now is in bool value, true means the joint is online(TODO).
    /// @return std::vector<uint16_t>: current joint status.
    std::vector<uint16_t> get_joint_status() const;


    /// @brief Get the current robot loco status.
    /// @return robot_status_t: current robot status.
    std::string get_robot_status() const;

    //std::vector<double> get_jump_status() const;


    /// @brief Get the current imu quaternion of mcu.
    /// @return std::array<double, 4>: current quaternion.
    std::array<double , 4> get_imu_quaternion() const;


    /// @brief Get the current imu acceleration of mcu.
    /// @return std::array<double, 3>: current acceleration.
    std::array<double, 3> get_imu_acceleration() const;

    /// @brief Get the current imu angular velocity of mcu.
    /// @return std::array<double, 3>: current angular velocity.
    std::array<double, 3> get_imu_angular_velocity() const;


    /// @brief Set the target joint feed-forward torques.
    /// @param t the target joint feed-forward torques.
    /// @return return true if the target is set successfully.
    bool set_joint_torque(const std::vector<double>& t);


    /// @brief Set mcu board can direct drive motors, default is auto_locomotion(use mcu control).
    /// @param if_sdk 
    /// @return return true if the target is set successfully
    bool set_motors_sdk(bool if_sdk);
  /**
     * @brief Set rc input to mcu. Only used in board mode is AUTO_LOCOMOTION.
     * @param forward the target forward.
     * @param yaw the target yaw.
     * @param pitch the target pitch.
     * @param roll the target roll.
     * @param height the target height.
     * @param split the target split.
     * @param tilt the target tilt.
     * @param forward_accel the target forward acceleration.
     * @param yaw_accel the target yaw acceleration.
     * @return return true if the target is set successfully
     */
    bool set_rc_input(can_device::api_channel_input_t input);



    /// @brief Set rc input to mcu. Only used in board mode is AUTO_LOCOMOTION.
    /// @param stand true if stand.
    /// @return return true if the target is set successfully
    bool set_robot_stand(bool stand);



    /// @brief Set rc input to mcu. Only used in board mode is AUTO_LOCOMOTION.
    /// @param jump true to start robot charge, then false change to start jump.
    /// @return return true if the target is set successfully
    bool set_robot_jump(bool jump);

  /**
     * @brief Set rc input to mcu. Only used in board mode is AUTO_LOCOMOTION.
     * @return return true if the target is set successfully
     */
    bool set_robot_stop();

    /// @brief Set rc input to mcu. Only used in board mode is AUTO_LOCOMOTION.
    /// @param down true if stand.
    /// @return return true if the target is set successfully
    bool set_robot_down(bool down);

private:
    std::unique_ptr<can_device::MotorsImuCanReceiveApi> can_receiver_;
    std::unique_ptr<can_device::MotorsCanSendApi> can_sender_;
    size_t motor_num_;
};//class tita_robot


















