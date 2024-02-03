package com.pucit.mobileapp.models;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.NonNull;

public class ListItemModel implements Parcelable {

    int img;
    String name;
    String description;

    public ListItemModel() {
        super();
    }

    public ListItemModel(int img, String name, String description) {
        this.img = img;
        this.name = name;
        this.description = description;
    }

    protected ListItemModel(Parcel parcel) {
        img = parcel.readInt();
        name = parcel.readString();
        description = parcel.readString();
    }

    public int getImg() {
        return img;
    }

    public void setImg(int img) {
        this.img = img;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(@NonNull Parcel parcel, int i) {
        parcel.writeInt(this.img);
        parcel.writeString(this.name);
        parcel.writeString(this.description);
    }

    private static final Creator<ListItemModel> CREATOR = new Creator<ListItemModel>() {
        @Override
        public ListItemModel createFromParcel(Parcel parcel) {
            return new ListItemModel(parcel);
        }

        @Override
        public ListItemModel[] newArray(int i) {
            return new ListItemModel[i];
        }
    };

//    public static final Creator<ListItemModel> CREATOR = new Creator<ListItemModel>() {
//        @Override
//        public ListItemModel createFromParcel(Parcel in) {
//            return new ListItemModel(in);
//        }
//
//        @Override
//        public ListItemModel[] newArray(int size) {
//            return new ListItemModel[size];
//        }
//    };

}
