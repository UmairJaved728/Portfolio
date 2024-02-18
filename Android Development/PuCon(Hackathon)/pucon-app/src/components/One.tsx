import {Image, IImageProps} from 'native-base'

type Props = IImageProps & {
    size: number
}

export function One({size, ...rest}: Props) {
    return (
        <Image
            w={size}
            h={size}
            borderRadius={'5px'}
            borderWidth={5}
            alt=""
            {...rest}
        />
    )
}
