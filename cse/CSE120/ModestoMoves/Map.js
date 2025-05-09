import React, { Component } from 'react';
import MapView from 'react-native-maps';
import {
    StyleSheet,
    Dimensions,
    View
} from react-native;

let {height, width} = Dimensions.get('window');

export default class Map extends Component{
  render(){
    return(
      <View style={styles.mapContainer}>
        <MapView
           style={styles.map}
           initialRegion={{
             latitude: 37.364216,
             longitude: -120.425419,
             latitudeDelta: 0.0922,
             longitudeDelta: 0.0421,
           }}
           showsUserLocation = {true}
           >
          <MapView.Marker
            coordinate={{
              latitude: 37.364216,
              longitude: -120.425419,
            }}
          />
        </MapView>
      </View>
      )
  }
}

const styles = StyleSheet.create({
    mapContainer: {
      height: height,
      width: width,
    },
    map: {
      ...StyleSheet.absoluteFillObject,
    },
});

