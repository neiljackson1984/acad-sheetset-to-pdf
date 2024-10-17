using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;

namespace AcSmSheetSetMgr
{
    public class AcSmCustomPropertyBag : AcSmClass
    {

        public AcSmCustomPropertyBag()
        {
            this.ClassName = "AcSmCustomPropertyBag";
            this.clsGuid = Guid.Parse("4D103908-8C86-4D95-BBF4-68B9A7B00731");
            this.fID = Guid.NewGuid();
            this.propname = "CustomPropertyBag";
            this.vt = 13;
        }

        public AcSmCustomPropertyBag(XmlElement wEl)            : base(wEl)
        {
        }

        public AcSmCustomPropertyValue GetProperty(string pName)
        {
            List<AcSmClass> wList = this.FindAllChild("AcSmCustomPropertyValue");
            if (wList != null)
            {
                if (wList.Exists(x => x.propname == pName))
                {
                    return (AcSmCustomPropertyValue)wList.Find(x => x.propname == pName);
                }
            }
            return null;
        }

        public AcSmCustomPropertyValue SetProperty(string pName, string pValue)   
        {
            AcSmCustomPropertyValue res = this.GetProperty(pName);
            if (res == null)
            {
                res = new AcSmCustomPropertyValue(pName, pValue);
                this.Child.Add(res);
            }
            else
            {
                res.Value = pValue;
            }
            return res;
        }

        public AcSmCustomPropertyValue SetProperty(int flag, string pName, string pValue)
        {
            AcSmCustomPropertyValue res = this.GetProperty(pName);
            if (res == null)
            {
                res = new AcSmCustomPropertyValue(flag, pName, pValue);
                this.Child.Add(res);
            }
            else
            {
                res.Value = pValue;
            }
            return res;
        }

    }
}
