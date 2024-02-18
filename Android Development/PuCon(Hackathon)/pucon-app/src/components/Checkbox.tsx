import React, {useState} from "react";
import {TouchableOpacity} from "react-native";
import {Image, Text, View} from "native-base";
import {THEME} from "../theme";
import Svg, {Path} from "react-native-svg";

interface CheckboxProps {
    label: string;
    isChecked: boolean;
    onToggle: (checked: boolean) => void;
}

export function Checkbox({label, isChecked, onToggle}: CheckboxProps) {
    const [checked, setChecked] = useState(isChecked);

    function toggleCheckbox() {
        const newCheckedState = !checked;
        setChecked(newCheckedState);
        onToggle(newCheckedState);
    }

    const CheckIcon = (

        <Svg width="13" height="13" viewBox="0 0 256 256">
            <Path
                fill={THEME.colors.Primary[100]}
                stroke={THEME.colors.Primary[100]}
                strokeWidth="15"
                d="M229.66,77.66l-128,128a8,8,0,0,1-11.32,0l-56-56a8,8,0,0,1,11.32-11.32L96,188.69,218.34,66.34a8,8,0,0,1,11.32,11.32Z"
            />
        </Svg>
    );

    return (<TouchableOpacity onPress={toggleCheckbox}>
            <View style={{flexDirection: 'row', alignItems: 'center'}}>
                <View
                    style={{
                        width: 14,
                        height: 14,
                        borderWidth: 1.5,
                        borderColor: THEME.colors.Primary[700],
                        borderRadius: 2,
                        marginRight: 5,
                        backgroundColor: checked ? THEME.colors.Primary[700] : 'transparent',
                        justifyContent: 'center',
                        alignItems: 'center',
                    }}
                >
                    {checked ? CheckIcon : null}
                </View>
                <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.xs}>{label}</Text>
            </View>
        </TouchableOpacity>
    );
}