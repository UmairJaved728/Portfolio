package com.pucit.mobileapp.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.pucit.mobileapp.R;
import com.pucit.mobileapp.interfaces.IRVListDTO;
import com.pucit.mobileapp.models.ListItemModel;

import java.util.ArrayList;

public class RVListAdapter extends RecyclerView.Adapter<RVListAdapter.MyViewHolder> {
    //meta data
    Context context;
    ArrayList<ListItemModel> listData = new ArrayList<>();

    IRVListDTO listDTO;
    public RVListAdapter(Context context, ArrayList<ListItemModel> listData) {
        this.context = context;
        this.listData = listData;
    }

    @NonNull
    @Override
    public RVListAdapter.MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.list_item, parent, false);
        return new MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RVListAdapter.MyViewHolder holder, int position) {
        final int idx = holder.getLayoutPosition();
        holder.name.setText(listData.get(position).getName());
        holder.description.setText(listData.get(position).getDescription());
        holder.userDp.setImageResource(listData.get(position).getImg());

        holder.linearLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                listDTO.sendData(listData.get(idx));
            }
        });
    }

    @Override
    public int getItemCount() {
        return listData.size();
    }

    public class MyViewHolder extends RecyclerView.ViewHolder {
        ImageView userDp;
        TextView name, description;

        LinearLayout linearLayout;
        public MyViewHolder(@NonNull View itemView) {
            super(itemView);
            userDp = itemView.findViewById(R.id.iv_icon);
            name = itemView.findViewById(R.id.tv_name);
            description = itemView.findViewById(R.id.tv_description);
            linearLayout = itemView.findViewById(R.id.idk);
        }
    }
}
