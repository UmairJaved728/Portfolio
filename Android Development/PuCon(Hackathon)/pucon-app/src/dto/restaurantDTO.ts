export type RestaurantDTO = {
    name: string
    location: {
        latitude: number
        longitude: number
    }
    rating: number
    description: string
    facilities: string[]
}
