import {ReactElement} from 'react'
import {Button, IButtonProps} from 'native-base'
import {THEME} from "../theme";

interface ButtonProps extends IButtonProps {
    message: string
    variant?: 'BLACK' | 'GREEN' | 'GRAY' | 'RED'
    onPress: () => void
    leftElement?: ReactElement
}

export function ButtonToken({
                                message,
                                variant = 'BLACK',
                                onPress,
                                leftElement = undefined,
                                ...rest
                            }: ButtonProps) {

    const getBackgroundColor = (selectedVariant: 'BLACK' | 'GREEN' | 'GRAY' | 'RED') => {
        switch (selectedVariant) {
            case 'BLACK':
                return THEME.colors.Primary[700];
            case 'GREEN':
                return THEME.colors.Secondary[500];
            case 'RED':
                return THEME.colors.Danger[500]; // Red background color
            default:
                return THEME.colors.Secondary[50];
        }
    };

    return (
        <Button
            leftIcon={leftElement !== undefined ? leftElement : undefined}
            borderRadius={'6px'}
            bgColor={getBackgroundColor(variant)}
            _text={{
                color: `${variant === 'GRAY' ? THEME.colors.Primary[300] : THEME.colors.Primary[100]}`,
                fontFamily: 'heading',
            }}
            onPress={onPress}
            {...rest}
        >
            {message}
        </Button>
    )
}
