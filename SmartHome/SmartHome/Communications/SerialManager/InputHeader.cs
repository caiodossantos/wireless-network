﻿#region Using Statements
using SmartHome.Communications.Messages;
using System;
using System.Collections.Generic;
#endregion

namespace SmartHome.Communications
{
    public class InputHeader
    {
        public enum ConfirmationType
        {
            None = 0,
            Ok,
            Error
        }

        #region Properties
        public bool SecurityEnabled { get; set; }

        public bool RoutingEnabled { get; set; }

        public ConfirmationType Confirmation { get; set; }

        public int MessageId { get; set; }

        public int EndPoint { get; set; }

        public int NextHop { get; set; }

        public int RSSI { get; set; }

        public OperationMessage Content { get; set; }
        #endregion

        public InputHeader()
        {
            this.Content = new OperationMessage();
        }

        public byte[] ToBinary()
        {
            List<byte> result = new List<byte>();

            byte headerByte = 0;

            if (SecurityEnabled)
                headerByte |= 0x80;

            if (RoutingEnabled)
                headerByte |= 0x40;
            
            headerByte |= (byte)(((byte)Confirmation) << 4);

            headerByte |= (byte)(EndPoint & 0x0F);

            result.Add((byte)MessageId);

            result.Add(headerByte);

            result.AddRange(BitConverter.GetBytes(NextHop));

            result.Add((byte)RSSI);

            if(Content != null)
                result.AddRange(Content.ToBinary());

            return result.ToArray();
        }

        public void FromBinary(byte[] buffer)
        {
            MessageId = buffer[0];

            SecurityEnabled = (buffer[1] & 0x80) != 0;

            RoutingEnabled = (buffer[1] & 0x40) != 0;

            Confirmation = (ConfirmationType)((buffer[1] >> 4) & 0x03);

            EndPoint = (buffer[1] & 0x0F);

            NextHop = (ushort)((((ushort)buffer[3]) << 8) | (ushort)buffer[2]);

            RSSI = (sbyte)buffer[4];

            if (buffer.Length > 5)
            {
                Content.FromBinary(buffer, 5);
            }
        }
    }
}
