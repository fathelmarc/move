#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseArray.h"

geometry_msgs::Pose datagyro;
void komCallback(const geometry_msgs::PoseArray& msg)
{
  datagyro.position.x += msg.poses[0].position.x;
  datagyro.position.y += msg.poses[1].position.y;
  datagyro.position.z += msg.poses[2].position.z;
  ROS_INFO("data blyat = [%f, %f, %f]", datagyro.position.x, datagyro.position.y, datagyro.position.z);
  /*fungsi ini akan dipanggil ketika node menerima pesan pada chatter topic. 
  pesan akan melewati (boost shared_ptr), yang mana kamu bisa menyimpan jika kamu mau
  tanpa mengkhawatirkan akan dihapus dibawah kamu, dan tanpa meng-copy tanpa data
  yang mendasari*/
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("ttg_imu", 1000, komCallback);
  // ros::Publisher p = n.advertise<geometry_msgs::Float64>("gc", 1000);
  /*subscribe ke chatter topic dengan masternya. ros akan memanggil chatterCallback()
  fungsi kapan pun pesan baru sampai. dalam kasus ini jika antrian sampai 1000 pesan
  kita akan mulai membuang pesan lama*/
  
  ros::spin();
  // while(ros::ok())
  // {
  //   // float gyro = datagyro;
  //   // gyro *= sin(45);
  //   // std_msgs::Float32 gyro_msg;
  //   // gyro_msg.data = gyro;
  //   // p.publish(gyro_msg);
  //   ros::spinOnce();
  // }
  /*memasuki loop dan akan memangil panggilan kembali secepat mungkin. ros::spin()
  akan berhenti jika ros::ok() kembali salah.*/
  return 0;
}