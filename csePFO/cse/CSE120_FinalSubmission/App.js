import * as React from 'react';
//import { Button, View, Text } from 'react-native';
import {useState} from 'react';
import {
  StyleSheet,
  Text,
  TextInput,
  View,
  ImageBackground,
  Image,
  Button,
  Alert,
  RefreshControl,
  Dimensions
} from 'react-native';
import { createAppContainer } from 'react-navigation';
import { createStackNavigator } from 'react-navigation-stack';
import { Calendar, CalendarList } from 'react-native-calendars';
//import Map from './components/Map';
import MapView from 'react-native-maps';
import logo from './images/logo2.png'


//const checkedIn = false;//useState('false');

export default class App extends React.Component {
    //const checkedIn = useState(false);
    render(){

        return <AppContainer />;
    }
}


class LoginScreen extends React.Component {
  render() {
    return (
      < ImageBackground style = {styles.container}>

            <View style={styles.top}
                style = {{alignItems: 'flex-start'}}
            >
                <Image source={logo} style={styles.logo}
                />
            </View>
            <TextInput
                placeholder="Username"
                style={{margin: 5, width: '80%', borderColor: 'black', borderWidth: 1, backgroundColor: 'white', padding: 10}}
            >
            </TextInput>
            <TextInput
                secureTextEntry={true}
                placeholder="Password"
                style={{margin: 5, width: '80%', borderColor: 'black', borderWidth: 1, backgroundColor: 'white', padding: 10}}
            >
            </TextInput>
            <View style={styles.button}>
            <Button
              title = "Login"
              color = 'black'
              onPress={() => this.props.navigation.navigate('Home')}
            />
            </View>
       </ImageBackground>

    )
  }
}
class HomeScreen extends React.Component {
    constructor(props) {
      super(props);
      this.state = { checkedIn: 0, };
    }
  render() {
    if(this.state.checkedIn == 0) {
            return(
            <ImageBackground style={styles.container}>

                <View style={styles.top}>
                  <Image source={logo} style={styles.logo} />
                </View>
                <View style={styles.button}>
                  <Button
                    title = "Check-In"
                    color = 'black'

                    onPress={() => this.setState(state => ({checkedIn: 1}))}
                    />

                </View>

                <View style={styles.button}>
                  <Button
                    title = "Event Calendar"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Calendar')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Statistics"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Statistics')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Profile"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Profile')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Track Runner"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Map')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Log Out"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Login')}
                  />
                </View>
          </ImageBackground>
          )
        } else {
            return(
            <ImageBackground style={styles.container}>

                <View style={styles.top}>
                  <Image source={logo} style={styles.logo} />
                </View>
                <View style={styles.button}>

                   <Button
                    title = "Check-Out"
                    color = 'black'
                    onPress={() => this.setState(state => ({checkedIn: 0}))}
                  />

                </View>

                <View style={styles.button}>
                  <Button
                    title = "Event Calendar"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Calendar')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Statistics"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Statistics')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Profile"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Profile')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Track Runner"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Map')}
                  />
                </View>

                <View style={styles.button}>
                  <Button
                    title = "Log Out"
                    color = 'black'
                    onPress={() => this.props.navigation.navigate('Login')}
                  />
                </View>
          </ImageBackground>
          )
        }



  }
}

class ProfileScreen extends React.Component {
  render() {
    return (
      <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
        <Text>Details Screen</Text>
        <Button
          title="Profile Page"
          onPress={() => this.props.navigation.push('Profile')}
        />
        <Button
          title="Go to Home"
          onPress={() => this.props.navigation.navigate('Home')}
        />
        <Button
          title="Return"
          onPress={() => this.props.navigation.goBack()}
        />
      </View>
    );
  }
}

class StatsScreen extends React.Component {
  render() {
    return (
      <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
        <Text>User Statistics</Text>
        <Button
          title="Reload Screen"
          onPress={() => this.props.navigation.push('Statistics')}
        />
        <Button
          title="Go to Home"
          onPress={() => this.props.navigation.navigate('Home')}
        />
        <Button
          title="Return"
          onPress={() => this.props.navigation.goBack()}
        />
      </View>
    );
  }
}


class CalendarScreen extends React.Component {
    render() {
        return (
            <View>
                <CalendarList
                    // Callback which gets executed when visible months change in scroll view. Default = undefined
                    onVisibleMonthsChange={(months) => { console.log('now these months are visible', months); }}
                    // Max amount of months allowed to scroll to the past. Default = 50
                    pastScrollRange={50}
                    // Max amount of months allowed to scroll to the future. Default = 50
                    futureScrollRange={50}
                    // Enable or disable scrolling of calendar list
                    scrollEnabled={true}
                    // Enable or disable vertical scroll indicator. Default = false
                    showScrollIndicator={true}

                    //...calendarParams
                    // Initially visible month. Default = Date()
                    
                    // Minimum date that can be selected, dates before minDate will be grayed out. Default = undefined
                    minDate={'2019-01-01'}
                    // Maximum date that can be selected, dates after maxDate will be grayed out. Default = undefined
                    maxDate={'2019-12-30'}
                    // Handler which gets executed on day press. Default = undefined
                    onDayPress={(day) => { console.log('selected day', day) }}
                    // Handler which gets executed on day long press. Default = undefined
                    onDayLongPress={(day) => { console.log('selected day', day) }}
                    // Month format in calendar title. Formatting values: http://arshaw.com/xdate/#Formatting
                    monthFormat={'MMMM yyyy'}
                    // Handler which gets executed when visible month changes in calendar. Default = undefined
                    onMonthChange={(month) => { console.log('month changed', month) }}
                    // Hide month navigation arrows. Default = false
                    hideArrows={true}
                    // Replace default arrows with custom ones (direction can be 'left' or 'right')
                    renderArrow={(direction) => (<Arrow />)}
                    // Do not show days of other months in month page. Default = false
                    hideExtraDays={false}
                    // If hideArrows=false and hideExtraDays=false do not switch month when tapping on greyed out
                    // day from another month that is visible in calendar page. Default = false
                    disableMonthChange={true}
                    // If firstDay=1 week starts from Monday. Note that dayNames and dayNamesShort should still start from Sunday.
                    firstDay={0}
                    // Hide day names. Default = false
                    hideDayNames={false}
                    // Show week numbers to the left. Default = false
                    showWeekNumbers={false}
                    // Handler which gets executed when press arrow icon left. It receive a callback can go back month
                    onPressArrowLeft={substractMonth => substractMonth()}
                    // Handler which gets executed when press arrow icon left. It receive a callback can go next month
                    onPressArrowRight={addMonth => addMonth()}
                />
            </View>
        );
    }
}

let {height, width} = Dimensions.get('window');

class MapScreen extends React.Component {
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

const RootStack = createStackNavigator({
  Login: LoginScreen,
  Home: HomeScreen,
  Calendar: CalendarScreen,
  Statistics: StatsScreen,
  Profile: ProfileScreen,
  Map: MapScreen,
},
{
 headerMode: 'none',
}
);

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#1167b1',
    alignItems: 'center',
    justifyContent: 'center',
  }, 
  top: {
    height: '50%',
    alignItems: 'center',
    justifyContent: 'center',
  },
  logo: {
    width: 300,
    height: 150,
    alignItems: 'flex-start'
  },
  button: {
    width:"80%",
    height: 40,
    margin: 10, 
    borderRadius: 20,
    backgroundColor: 'orange'
  },
  mapContainer: {
    height: height,
    width: width,
  },
  map: {
    ...StyleSheet.absoluteFillObject,
  },

  /* buttonStyle: {
    flex: 1,
    alignSelf: 'stretch',
    backgroundColor: '#fff',
    borderRadius: 5,
    borderWidth: 1,
    borderColor: '#007aff',
    marginLeft: 5,
    marginRight: 5
  }, 
  textStyle: {
    alignSelf: 'center',
    color: '#007aff',
    fontSize: 16,
    fontWeight: '600',
    paddingTop: 10,
    paddingBottom: 10
  } */

});

const AppContainer = createAppContainer(RootStack)
//export default createAppContainer(RootStack);
// @refresh reset