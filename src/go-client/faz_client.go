package main

import (
	"context"
	"fmt"
	faz "github.com/hao-liu-1117/csci499_hao-liu-1117/src/proto/faz"
	"google.golang.org/grpc"
)

func Hook(client faz.FazServiceClient, e_type int32, e_func string) bool {
	req := &faz.HookRequest{EventType: e_type, EventFunction: e_func}
	_, err := client.Hook(context.Background(), req)
	if err != nil {
		return false
	}
	return true
}

func Unhook(client faz.FazServiceClient, e_type int32) bool {
	req := &faz.UnhookRequest{EventType: e_type}
	_, err := client.Unhook(context.Background(), req)
	if err != nil {
		return false
	}
	return true
}

func Event(client faz.FazServiceClient, req *faz.EventRequest) *faz.EventReply {
	rep, err := client.Event(context.Background(), req)
	if err != nil {
		return nil
	}
	return rep
}

func IsRegistered(client faz.FazServiceClient, e_func string) int32 {
	req := &faz.IsRegisteredRequest{EventFunction: e_func}
	rep, err := client.IsRegistered(context.Background(), req)
	return rep.EventType
}

func main() {
	conn, err := grpc.Dial("localhost:50000", grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		fmt.Println("failed to connect")
		return
	}
	defer conn.Close()
	c := faz.NewFazServiceClient(conn)
	Hook(c, 1, "registeruser")
}