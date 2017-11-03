// ptree.cpp : Defines the entry point for the console application.
//

#if defined( WIN32 ) || defined( WIN64 )
#include "stdafx.h"
#endif

#include <cassert>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#if 0
  void camera_config::load_config( const std::string& f_configure ) {
    try {
      boost::property_tree::ptree pt;
	    boost::property_tree::read_xml( f_configure, pt );
      for( boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); it++ )
           std::cout << "Here " << it->first << " " << std::endl;
      BOOST_FOREACH( boost::property_tree::ptree::value_type& p1, pt.get_child( "fast_camera.config" ) ) {
        boost::property_tree::ptree& p = p1.second.get_child( "<xmlattr>" );
        axis_x_min = p.get< float >( "axis_x_min" );
        axis_x_max = p.get< float >( "axis_x_max" );
        axis_x_scene_zero = p.get< float >( "axis_x_scene_zero" );
        axis_x_scene_range = p.get< float >( "axis_x_scene_range" );
        axis_y_min = p.get< float >( "axis_y_min" );
        axis_y_max = p.get< float >( "axis_y_max" );
        axis_y_scene_zero = p.get< float >( "axis_y_scene_zero" );
        axis_y_scene_range = p.get< float >( "axis_y_scene_range" );
        axis_z_min = p.get< float >( "axis_z_min" );
        axis_z_max = p.get< float >( "axis_z_max" );
        axis_z_scene_zero = p.get< float >( "axis_z_scene_zero" );
        axis_z_scene_range = p.get< float >( "axis_z_scene_range" );
        axis_dist_min = p.get< float >( "axis_dist_min" );
        axis_dist_max = p.get< float >( "axis_dist_max" );
        axis_dist_scene_zero = p.get< float >( "axis_dist_scene_zero" );
        axis_dist_scene_range = p.get< float >( "axis_dist_scene_range" );
      }
      
    }
    catch( const boost::property_tree::ptree_error& e ) {
      std::cerr << e.what() << std::endl;
    }
    return;
  }

#endif

const char* file = "fast_camera.xml";

#if defined( WIN32 ) || defined( WIN64 )
int _tmain( int ac, _TCHAR* av[] ) {
#else
int main( int ac, char* av[] ) {
#endif
  try {
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml( file, pt );
    for( boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); it++ ) {
      std::cout << "Here " << it->first << " " << std::endl;
      for( boost::property_tree::ptree::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++ ) {
        std::cout << "Here1 " << it1->first << " " << std::endl;
        for( boost::property_tree::ptree::const_iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++ ) {
          std::cout << "Here2 " << it2->first << " " << std::endl;
          if( "property" == it2->first ) {
            const boost::property_tree::ptree& p = it2->second.get_child( "<xmlattr>" );
            std::cout << "" << p.get< int >( "axis_x_min" ) << std::endl;
          }
        }        
      }
    }
  }
  catch( const boost::property_tree::ptree_error& e ) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}

