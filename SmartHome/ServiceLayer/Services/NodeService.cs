﻿#region Using Statements
using DataLayer.Entities.Enums;
using ServiceLayer.DTO;
using System; 
#endregion

namespace ServiceLayer
{
    public class NodeService
    {
        /// <summary>
        /// Conecta un conector con un home device
        /// </summary>
        /// <param name="connector"></param>
        /// <param name="homeDevice"></param>
        /// <returns>0 == OK, 
        /// 1 == el conector estaba ya ocupado por un home Device
        /// 2 == el homeDevice ya estaba conectado en un conector diferente al nuevo
        /// 3 == el homeDevice no es compatible con el conector</returns>
        public int LinkHomeDevice(int idConnector, int idHomeDevice)
        {
            throw new NotImplementedException();

            //Connector connector = //GET CONECTOR BY ID
            //HomeDevice homeDevice = //GET HOMEDEVICE BY ID

            //if (connector.InUse)
            //    return 1;
            
            //if (homeDevice.InUse)
            //    return 2;

            //connector.LinkHomeDevice(homeDevice);
            //homeDevice.LinkConnector(connector);

            //return 0;
        }


        /// <summary>
        /// Desrelaciona un HomeDevice de su conector asociado
        /// </summary>
        public void UnlinkHomeDevice(int idHomeDevice)
        {
            throw new NotImplementedException();

            //HomeDevice homeDevice = //GET HOMEDEVICE BY ID
            //homeDevice.Connector.UnlinkHomeDevice();
            //homeDevice.UnlinkConnector();
        }

        /// <summary>
        /// Devuelve los conectores que pertenecen a un NODO
        /// </summary>
        /// <param name="node"></param>
        /// <returns>Dicionario IDConnector, nombre, tipo, en uso</returns>
        public ConnectorDTO[] GetConnectors(int idNode)
        {
            throw new NotImplementedException();

            //var connectors = NetworkManager.Nodes.First(n => n.Id == idNode).Connectors;

            //return Mapper.Map<List<ConnectorDTO>>(connectors).ToArray();
        }


        /// <summary>
        /// Devuelve los conectores que se pueden conectar con el homeDevice enviado por parametros
        /// </summary>
        /// <param name="HomeDeviceType"></param>
        /// <returns></returns>
        public ConnectorDTO[] GetConnectorsCapable(int idHomeDevice, int idNode)
        {
            throw new NotImplementedException();
            //HomeDevice homeDev = NetworkManager.HomeDevices.First(hd => hd.Id == idHomeDevice);

            //var connectors = NetworkManager.Nodes.First(n => n.Id == idNode).Connectors.Where(c => c.ConnectorType == homeDev.ConnectorCapable);

            //return Mapper.Map<List<ConnectorDTO>>(connectors).ToArray();
        }

        public string GetNameNode(int idNode)
        {
            throw new NotImplementedException();
            //return NetworkManager.Nodes.First(n => n.Id == idNode).Name;
        }

        public void SetNameNode(int idNode, string newName)
        {
            throw new NotImplementedException();
            //NetworkManager.Nodes.First(n => n.Id == idNode).Name = newName;
        }

        public int GetAddressNode(int idNode)
        {
            throw new NotImplementedException();
            //return NetworkManager.Nodes.First(n => n.Id == idNode).Address;
        }

        public void SetAddressNode(int idNode, ushort newAddress)
        {
            throw new NotImplementedException();
            //NetworkManager.Nodes.First(n => n.Id == idNode).Address = newAddress;
        }

        public void UpdatePosition(int idLocation, float x, float y)
        {
            throw new NotImplementedException();
        }

        public LocationDTO GetNodePosition(int idNode)
        {
            throw new NotImplementedException();
            //return NetworkManager.Nodes.First(n => n.Id == idNode).Position;
        }

        /// <summary>
        /// Devuelve el id del conector, su nombre, tipo
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public ConnectorDTO[] GetFreeConnectors(int idNode)
        {
            throw new NotImplementedException();
            //var connectors = NetworkManager.Nodes.First(n => n.Id == idNode).Connectors.Where(c => c.InUse == false);

            //return Mapper.Map<List<ConnectorDTO>>(connectors).ToArray();
        }

        public NodeDTO[] GetNodes()
        {
            throw new NotImplementedException();
            //return Mapper.Map<List<NodeDTO>>(NetworkManager.Nodes).ToArray();
        }

        public NodeDTO[] GetNodes(int idZone)
        {
            throw new NotImplementedException();
            //var nodes = NetworkManager.Nodes.Where(n => n.Position.Id == idZone);

            //return Mapper.Map<List<NodeDTO>>(nodes).ToArray();
        }

        /// <summary>
        /// Obtain the types of shields
        /// </summary>
        /// <returns></returns>
        public string[] GetTypesShields()
        {
            return Enum.GetNames(typeof(ShieldTypes));
        }

        /// <summary>
        /// Obtain the types of bases
        /// </summary>
        /// <returns></returns>
        public string[] GetTypesBases()
        {
            return Enum.GetNames(typeof(BaseTypes));
        }
    }
}