import React from 'react';
import { View, Text, StyleSheet, TouchableOpacity } from 'react-native';

// Touchable is another feature 
// not a component, more of a parent class
// can be wrapped around views
// onPress={props.onDelete} - forwarding onDelete to onPress

const GoalItem = props => {
    return (
        <TouchableOpacity onPress={props.onDelete}>
            <View style={styles.listItem}>
                <Text>{props.title}</Text>
            </View>
        </TouchableOpacity>
    );
};

const styles = StyleSheet.create({
    listItem: {
        padding: 10,
        marginVertical: 10,
        backgroundColor: '#ccc',
        borderColor: 'black',
        borderWidth: 1

    }
});

export default GoalItem;